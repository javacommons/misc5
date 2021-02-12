// https://boostjp.github.io/tips/variant.html
#include <boost/variant.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

using property_type = boost::make_recursive_variant
< bool
, float, double, long double
, std::vector< boost::recursive_variant_ >
, std::unordered_map< std::string, boost::recursive_variant_ >
>::type;

using array_type = std::vector< property_type >;
using map_type   = std::unordered_map< std::string, property_type >;

class printer
  : boost::static_visitor< void >
{
  std::ostream& _s;
  const std::size_t _nest_level = 0;

  public:

  explicit printer( std::ostream& s, const std::size_t nest_level = 0 )
    : _s( s )
    , _nest_level( nest_level )
  { }

  auto indent( const std::size_t delta_nest_level = 0 ) const
  {
    for ( std::size_t n = 0; n < _nest_level + delta_nest_level; ++ n )
      _s << "  ";
  }

  auto operator()( const array_type& o ) const -> void
  {
    indent();
    _s << "[\n";
    for ( auto i = o.cbegin(); i != o.cend(); ++i )
    {
      boost::apply_visitor( printer( _s, _nest_level + 1 ), *i );
      if ( i + 1 != o.cend() )
        _s << ",";
      _s << "\n";
    }
    indent();
    _s << "]";
  }

  auto operator()( const map_type& o ) const -> void
  {
    indent();
    _s << "{\n";
    for ( auto i = o.cbegin(); i != o.cend(); )
    {
      indent( 1 );
      _s << '"' << i->first << '"' <<  ":\n";
      boost::apply_visitor( printer( _s, _nest_level + 2 ), i->second );
      if ( ++i != o.cend() )
        _s << ",";
      _s << "\n";
    }
    indent();
    _s << "}";
  }

  auto operator()( const bool e ) const -> void { indent(); _s << std::boolalpha << e; }

  template < typename T >
  auto operator()( const T e ) const -> void { indent(); _s << std::fixed << std::setprecision( std::numeric_limits< T >::max_digits10 - 2 ) << e; }
};

auto main() -> int
{
  array_type p1;
  p1.emplace_back( 1.23e-4f );
  p1.emplace_back( 1.23e-4 );
  p1.emplace_back( 1.23e-4l );
  p1.emplace_back( true );
  p1.emplace_back( p1 );
  map_type p2;
  p2.emplace( "fuga", p1 );
  p2.emplace( "piyo", false );
  p1.emplace_back( p2 );
  property_type p = p1;

  boost::apply_visitor( printer( std::cout ), p );
}
