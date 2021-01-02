// A map_aligner osztály template, ami az
// add művelet vagy operator+= segítségével összegyűjti, hogy melyik 
// std::map-ekkel kell dolgoznia. A map_aligner template paraméterei
// nyilván leírják a mapek template paramétereit. Az align() művelet az
// összegyűjtött mapeket egyenletesre igazítja: mindegyik map-ben az összes
// olyan kulcs szerepelni fog, amelyik valamelyik map-ben benne volt.
// Alapértelmezetten a kulcstípus default konstruáltját rendeli az align() a
// map azon kulcsaihoz, ami korábban nem szerepelt benne, de egy másikban
// igen. A set_filler művelettel ez az érték felülírható. A count() megadja,
// hogy hány map-et érint a kiigazítás. A map-eket nem
// szükséges, hogy alapértelmezett rendelkezéssel rendezzék. Van még egy
// erase művelet: ha a map kulcs és érték típusa eltér, akkor az összes
// map-ből törlendő az erase kulcs paramétere. Viszont, ha a map kulcs és
// értéktípusa megegyezik, akkor akár kulcsként törölni kell az összes mapből
// (rendezés alapján), akár értékként (egyenlőségvizsgálattal), ez utóbbi
// esetben, az összes ilyen kulcsú elemet törölni kell a map-ekből.

#include <iostream>
#include "mapalign.h"
#include <string>
#include <algorithm>
#include <map>

struct string_size_less
{

  bool operator()( const std::string& a,
                   const std::string& b ) const
  {
    return a.size() < b.size();
  }

};

const int max = 1000;

bool check()
{

  std::map<std::string, int> sma;
  std::map<std::string, int> smb;
  std::map<std::string, int> smc;

  map_aligner<std::string, int> sa;
  
  sa.add( sma );
  sa.add( smb );
  sa.add( smc );

  sma[ "C++" ] = 1;
  smb[ "Ada" ] = 2;
  smc[ "C" ] = 3;
  smc[ "Python" ] = 4;
  smc[ "Ada"] = 5;

  sa.align();

  std::map<int, double> ima;
  std::map<int, double> imb;
  for( int i = 0; i < max; ++i )
  {
    if ( 0 == i % 2 )
    {
      ima[ i ] = max - i;
    }
    else
    {
      imb[ i ] = max;
    }
  }

  map_aligner<int, double> ia;
  ia.add( ima );
  ia.add( imb );

  ia.align();

  if ( 4 != sma.size() && 1 != imb.count( 0 ) || max * 1U != ima.size() ||
       1 != smc.count( "C++" ) || "Ada" != sma.begin()->first ||
       0 != sma.begin()->second ||  4 != smc.size() ||
       1 != smb.count( "Python" ) || 0 != imb.begin()->first ||
       0.8 <= imb.begin()->second || 1 != imb.count( max / 2 ) )
  {
    return false;
  }

  sma[ "Pascal" ] = 5;
  sa.set_filler( max );
  sa.align();

  std::map<std::string, std::string> langsa;
  langsa[ "C++" ] = "<3";
  langsa[ "Python" ] = ":|";
  std::map<std::string, std::string> langsb;
  langsb[ "Brainfuck" ] = ":S";
  langsb[ "Python" ] = ":/";
  langsb[ "C" ] = ":)";

  map_aligner<std::string, std::string> lsa;
  lsa.add( langsa );
  lsa.add( langsb );

  lsa.align();
  lsa.erase( "Python" );

  if ( 0 != langsa.count( "Python" ) || max != smc[ "Pascal" ] ||
       !langsa.begin()->second.empty() || max != smb[ "Pascal" ] ||
       2 * 1U != langsb.begin()->second.size() ||
       0 != langsb.count( "Python" ) || 1 != langsb.count( "C++" ) )
  {
    return false;
  }

  std::map<std::string, std::string, string_size_less> lma;
  std::map<std::string, std::string, string_size_less> lmb;
  std::map<std::string, std::string, string_size_less> lmc;

  lma[ "C++" ] = ":D";
  lmb[ "Eiffel" ] = ":P";
  lmc[ "C" ] = "8-)";
  lmc[ "Ada" ] = "!";

  map_aligner<std::string, std::string, string_size_less> ls;
  ls.add( lma );
  (ls += lmb) += lmc;

  ls.align();

  return ( 3 == ls.count() && 1 == lmc.count( "Ada" ) &&
       3 * 1U == lmb.size() && 1 == lma.count( "Python" ) &&
       2 == lsa.count() && 2 == ia.count() );
}

int main()
{
  std::cout
    << "Your solution is " << (check() ? "" : "not ")
    << "ready for submission.\n";
}
