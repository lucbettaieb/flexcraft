// File:           demo.cpp
// Creation Date:  Tuesday, September 29 2009
// Author:         Julius Ziegler <ziegler@mrt.uka.de>

#include <iostream>

#include <boost/program_options.hpp>

#include "StarGazer.hpp"

int ref_id;
int no_ids;

std::string device;
std::string id_type;

int id_dim;

void parse_commandline( int argc, char** argv )
{
  namespace po = boost::program_options;

  using namespace std;

  // parse program options
  po::options_description desc("Allowed options");
  desc.add_options()
    ( "help,h", "produce help message" )
    ( "reference-id,r", po::value<int>( &ref_id )->default_value( 18966 ), "use this as reference id" )
    ( "no-ids,n", po::value<int>( &no_ids )->default_value( 11 ), "learn this number of ids" )
    ( "device-node,d", po::value<string>( &device )->default_value( "/dev/ttyUSB0" ), "device node of serial port" )
    ( "id-type,t", po::value<string>( &id_type )->default_value( "Home" ), "Type of ids: 3x3 (\"Home\") or 4x4 (\"Office\")" )
    ( "id-dim,s", po::value<int>( &id_dim )->default_value( 3 ), "Dimension of ids, 1-3" )
    ;

  po::variables_map vm;
  try
    {
      po::store( po::parse_command_line( argc, argv, desc ), vm );
      po::notify( vm );
    } 
  catch( ... )
    {
      std::cout << "Usage: \n\n" << desc << std::endl;
      exit( 1 );
    }
  
  if (vm.count("help")) {
    std::cout << desc << "\n";
    exit( 0 );
  }
}


int main( int argc, char** argv )
{
  parse_commandline( argc, argv );

  StarGazer sg( device );

  // set mark mode to "Map" (alternative is "Alone")
  // sg.write_parameter( "MarkMode", "Map" );
  // sg.write_parameter( "MarkType", "HLD1L" );

  /*
  sg.write_parameter( "MarkMode", "Alone" );
  sg.start_calc();

  while( true )
    {
      std::string loc = sg.get_string();
      if( loc != "" ) std::clog << loc << "\n";
      else std::clog << ".";
    }
  */

  std::clog << "MarkMode \t"   << sg.read_parameter( "MarkMode" )  << "\n";
  std::clog << "HeightFix: \t" << sg.read_parameter( "HeightFix" ) << "\n";
  std::clog << "MarkType: \t"  << sg.read_parameter( "MarkType" )  << "\n";
  std::clog << "MarkDim: \t"  << sg.read_parameter( "MarkDim" )  << "\n";
	
	sg.start_calc();

	while(true)
	{
		StarGazer::PositionData pd;

		pd = sg.get_position().back();
		
		if( pd.dead )
			std::cout << "dead!\n";
		else
			std::cout << "x, y, z, theta: " << pd.x << ", " << pd.y << ", " << pd.z << ", " << pd.theta << "\n";
	}
}
