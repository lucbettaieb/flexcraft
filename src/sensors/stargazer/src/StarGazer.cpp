// File:           StarGazer.cpp
// Creation Date:  Tuesday, September 29 2009
// Author:         Julius Ziegler <ziegler@mrt.uka.de>

#include <unistd.h>
#include <cmath>

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "StarGazer.hpp"
#include "serial_port.hpp"

// #define USE_LIBSERIAL

//#define PRINT_STRINGS 1
//#define PRINT_STRINGS_CHARBYCHAR 1

StarGazer::StarGazer( std::string device ):
  ser_fd( initport( device ) )
{    
  if( ser_fd < 0 )
    { 
      throw( std::runtime_error( "cannot connect to serial port @ " + device ) );     
    }
  
  std::clog << "Connected to StarGazer using device " << device << ".\n";

  stop_calc();

  std::clog << "Firmware version: " << read_parameter( "Version" ) << "\n";

}

std::string StarGazer::read_parameter( const std::string parameter )
{
  send_command_string( "~@" +parameter + "`" );
 
  std::string response;
  response = get_string();
  
  unsigned int separator_idx = response.find( '|' );

  if( separator_idx == std::string::npos )
    return "XXXXXX";

  // response looks like this: ~$Parameter|Value'.
  // Strip everything except Value.  
  
  response = response.substr( response.find( '|' ) + 1 );
  response = response.substr( 0, response.size() - 1 );
  
  return response;
}

template<class T> T StarGazer::read_parameter_as( const std::string parameter );


std::string StarGazer::command_string( const std::string command )
{
  return std::string( "~#" ) + command + "`";
}

void StarGazer::flush_stargazer_buffer()
{
  // read everything and discard it, until read timeouts
  std::string garbage = get_string();

  while( garbage != "" )
    {
      //      std::clog << "discarded: " << garbage << "\n"; 
      // std::clog << ".";
      std::clog << "garbage: " << garbage << "\n";
      garbage = get_string();
    }
  std::clog << "\n";
}

void StarGazer::build_map( int no_markers, int ref_marker_id )
{
  std::vector<int> ids;
  
  stop_calc();

  write_parameter( "IDNum", no_markers );
  write_parameter( "RefID", ref_marker_id );
  write_parameter( "MarkMode", "Map" );

  // Documentation says an extra ~#CalcStart` is necessary here,
  // but following command triggers calculation by it self:

  send_command_string( "~#MapMode|Start`" );
    

  // these datastructures records the minimum spanning tree for verification and debugging.
  std::vector< std::pair<int, int> >  edges;
  std::map<int, PositionData>         id_map;
  
  PositionData parent;
  parent.id = 0;

  while( true ) {
    std::string str = get_string();

    std::clog << "\v";

    std::vector<PositionData> pds = parse_position_msg( str );
    PositionData pd = pds[0];

    if( !pd.dead ) {
      std::clog << "FIX: " << pd.id << "\n";
      id_map[pd.id] = pd;
      parent = pd;
    }
    else
      std::clog << "NO FIX, last was " << parent.id << "\n";

    std::clog << "\nGot these ids:\n";

    BOOST_FOREACH( int id, ids )
      std::clog << id << "\n";
     
    std::clog << "\b\b\n";

    if( str.size() >= 5 && str.substr( 2, 5 ) == "MAPID" )
      {
	std::cout << "cast: " << str.substr( 8, str.size() - 9 ) << "\n";
	int id = boost::lexical_cast<int>( str.substr( 8, str.size() - 9 ) );
	std::clog << "\n" << "got ID " << id << "\n";
	ids.push_back( id );
	edges.push_back( std::make_pair( id, parent.id ) );
      }

    if( str == "~!MapDataSave`" )
      {
	std::clog << "\nmap saved.\n";
	break;
      }
  }

  // output the spanning tree (gnuplot format)
  std::ofstream os( "spanning_tree" );
  std::pair<int,int> e;
  BOOST_FOREACH( e, edges )
    {
      std::cout <<  e.second << "->" << e.first << "\n";
      
      PositionData child  = id_map[ e.first ];
      PositionData parent = id_map[ e.second ];
      os << parent.x << " " << parent.y << "\n";
      os << child.x << " " << child.y << "\n";
      os << " \n \n";
    }

  stop_calc();
}

std::vector<StarGazer::PositionData> StarGazer::get_position()
{
  return parse_position_msg( get_string() );
}

double StarGazer::calc_height()
{
  stop_calc();

  send_command_string( command_string( "HeightCalc" ) );

  std::clog << "calculating height...\n";

  while( true )
    {
      std::string msg = get_string();
      std::clog << ".";
      if( msg == "~!ParameterUpdate`" )
	{
	  break;
	}
    }

  std::clog << "\n";

  stop_calc();

  int height_mm = read_parameter_as<int>( "MarkHeight" );



  return height_mm/1000.;
  
}


void StarGazer::start_calc()
{
  std::clog << "sending CalcStart ...\n";
  send_command_string( command_string( "CalcStart" ) );
}

void StarGazer::stop_calc()
{
  // must repeat this until success (see manual)
  std::clog << "stop calc...\n";

  //flush_stargazer_buffer();
  bool success = false;
  while( !success )
    {
      try {
	std::clog << "sending CalcStop...\n";
	send_command_string( command_string( "CalcStop" ) );
	success = true;
      } catch( std::runtime_error e )
	{
	  std::clog << e.what() << "\n";
	  success = false;
	  // make sure the buffer is empty:
	  //flush_stargazer_buffer();
	}
    }

  flush_stargazer_buffer();
}

void StarGazer::send_command_string( const std::string str )
{
  std::string cpy = str;
  send_string( str );
  cpy[1] = '!';
  std::string ack = get_string();
  if( !( cpy == ack ) )
    {
      throw( std::runtime_error( "command " + str + " did not return correct acknowledge " + cpy + " ( returned " + ack + " )" ) );     
    }
}

/*
void StarGazer::send_command_string( const std::string str )
{
  std::clog << "sending command string: " << str << "\n";

  std::string cpy = str;;
  cpy[1] = '!';
  send_string( str );

  std::string ack;
  do {
    ack = get_string();
    std::clog << "ack: " << ack << "\n";
  }
  while( cpy != ack );
}
*/

void StarGazer::send_string( const std::string str )
{
  BOOST_FOREACH( char c, str )
    {      
      if( write( ser_fd, &c, 1 ) != 1 )
 	throw( std::runtime_error( "write failed!" ) );

      usleep( 50000 );
    }
}

/** reads until the end of sentence character: "`"**/
std::string StarGazer::get_string()
{  
  std::string result;

  char c;

  do {

#ifdef PRINT_STRINGS_CHARBYCHAR
    std::clog << "read...\n";
#endif

    int no_read = read( ser_fd, &c, 1 );

#ifdef PRINT_STRINGS_CHARBYCHAR
         std::cout << "read " << no_read << "\n";
    std::clog << "...done.\n";
#endif

    if( no_read == 0 )
      return "";

#ifdef PRINT_STRINGS_CHARBYCHAR
    std::clog << "[" << (unsigned int)c << "]" << "\n";
#endif

    if( (unsigned int)(c) <= 32 || (unsigned int)(c) > 127 ) 
      return "";

    result.push_back( c );
  } while( c != '`' && result.size() < 70 );

#ifdef PRINT_STRINGS
  std::clog << "got string: " << result <<"\n";
#endif

  return result;
}

void StarGazer::acknowledge_parameter_update()
{
  std::clog << "wait for parameter update acknowledge (this may take some seconds)...\n";
  std::string str = get_string();
  
  while( str == "" ) 
    {
      std::clog << ".";
      str = get_string();
    }

  std::clog << "\n";

  if( str != "~!ParameterUpdate`" )
    throw( std::runtime_error( std::string( "did not receive expected message: ~!ParameterUpdate` after writing parameter; received " ) + str) );     
}

std::string StarGazer::consume_token( std::string& str )
{
  unsigned int idx = str.find( '|' );			\
  if( idx == std::string::npos )
    return "XXXXXXX";

  //  std::clog << "consume_token, idx: " << idx << "\n";
  std::string token = str.substr( 0, idx );
  str = str.substr( idx + 1 );
  return token;
}

std::vector<StarGazer::PositionData> StarGazer::parse_position_msg( std::string str )
{
  std::vector<PositionData> result(1);

  try {

    if( str == "~*DeadZone`" )
      {
	result[0].dead = true;
	return result;
      }

    if( str.size() < 5 ) // read timeout?
      {
	result[0].dead = true;
	return result;
      }

    //Check how many readings stargazer received
    int num_readings;
    //1-id mode. Reading an I indicates map mode
    if (str.at(2) == 'I')
    {
	std::cout << "at 2: " << str.at(2) << std::endl;
	num_readings = 1;
    } else {
	//2-id mode. Message contains number of ids seen
        num_readings = boost::lexical_cast<int> (str.substr(2, 1));
    }

    if (num_readings == 2)
    {
      result.resize(num_readings);
    }


    str = str.substr( 3 );

    
    // primitive tokenizer expects | termination
    str[ str.size() - 1 ] = '|';

    //read available data
    size_t marker_ind;
    for ( marker_ind=0; marker_ind < num_readings; marker_ind++)
    {
      result[marker_ind].dead = false;
      result[marker_ind].id    =  boost::lexical_cast<int>( consume_token( str ) );


      // stargazer inverts angle!
      result[marker_ind].theta = -boost::lexical_cast<double>( consume_token( str ) );

      result[marker_ind].x = boost::lexical_cast<double>( consume_token( str ) );
      result[marker_ind].y = boost::lexical_cast<double>( consume_token( str ) );
      result[marker_ind].z = boost::lexical_cast<double>( consume_token( str ) );
      
      result[marker_ind].x *= 0.01;
      result[marker_ind].y *= 0.01;
      result[marker_ind].z *= 0.01;

      result[marker_ind].theta *= M_PI/180.;
    }
    
      return result;
  }
  catch( std::exception e )
    {
      std::clog << "StarGazer::parse_position_msg(): caught error: " << e.what() << "\n"; 
      for (size_t marker_ind=0; marker_ind < result.size(); marker_ind++)
      {
        result[marker_ind].dead = true;
      }
      return result;
    }
}
