// File:           StarGazer.hpp
// Creation Date:  Tuesday, September 29 2009
// Author:         Julius Ziegler <ziegler@mrt.uka.de>

#if !defined(STARGAZER_HPP)
#define STARGAZER_HPP

#include <string>
#include <boost/lexical_cast.hpp>

class StarGazer {
public:

  struct PositionData 
  {
    PositionData(): dead( false ), id( 0 ), x( 0 ), y( 0 ), z( 0 ), theta( 0 ) {}
    
    bool dead;    
    int id;
    double x, y, z, theta;        
  };
      
  StarGazer( std::string device = "/dev/ttyS0" );

  std::vector<PositionData> get_position();

  /** run map building. Takes number of markers and reference marker id as
      parameters. **/
  void build_map( int no_markers, int ref_marker_id );
    
  /**
     This is a list of possible values for parameter
     (copied from manual, see there for details):
     Version, IDNum, RefID, HeightFix,
     MarkHeight, MarkType, MarkMode, BaudRate, 
     HeightCalc, MapMode, CalcStart, 
     CalcStop, SetEnd, Reset
  **/
  std::string read_parameter( const std::string parameter );

  /**
     This is a templated version of above method that does
     a lexical cast of the value string.
     
     Example:
     double height = sg.read_parameter_as<double>( "MarkHeight" );
  **/
  template<class T> T    read_parameter_as( const std::string parameter )
  { return boost::lexical_cast<T>( read_parameter( parameter ) ); }

  template<class T> void write_parameter( const std::string parameter, const T value );

  /** calculate height of a single marker in field of view.
      Only used this for testing. **/
  double calc_height();
  
  /** The manual recommends bracketing parameter
      reads/writes and commands with stopping/restarting
      position calculation.

      These functions send the respective command strings. **/
  void start_calc();
  void stop_calc();  

  /** get a "raw" string out of the device. Reads until
      '`' is seen. **/
  std::string get_string();

private:
  static std::string command_string( const std::string command );
  void flush_stargazer_buffer();

  void send_command_string( const std::string str );
  void send_string( const std::string str );

  void acknowledge_parameter_update();

  static std::string consume_token( std::string& str );
  static std::vector<PositionData> parse_position_msg( std::string str );

  // SerialPort ser;
  int ser_fd;
};

template<class T> void StarGazer::write_parameter( const std::string parameter, const T value )
{
  send_command_string( "~#" +parameter + "|" + boost::lexical_cast<std::string>( value ) + "`" );
  send_command_string( "~#SetEnd`" );

  acknowledge_parameter_update();
}

#endif
