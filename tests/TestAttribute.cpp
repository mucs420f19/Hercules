#include "../Attribute.h"

#include "catch2/catch.hpp"

std::ostream &
operator<<(std::ostream& os, Visibility const & v) {
  os << ToStringVis(v);
  return os;
}

bool
operator==(Visibility const& a, Visibility const& b)
{
  return static_cast<int>(a) == static_cast<int>(b);
}

bool
operator!=(Visibility const& a, Visibility const& b)
{
  return static_cast<int>(a) != static_cast<int>(b);
}

TEST_CASE("Attributes work")
{
  std::string name ("test");
  Visibility vis = Visibility::PUBLIC;
  Attribute a (name, vis);
  REQUIRE (a.visibility() == ToStringVis(vis));
  REQUIRE (a.name() == name);

  SECTION("Attribute can have visibility change")
  {
    a.setVisibility(Visibility::PRIVATE);
    REQUIRE(a.visibility() == ToStringVis(Visibility::PRIVATE));
  }

  SECTION("Attribute can have name change")
  {
    std::string newName ("newName");
    a.setName(newName);
    REQUIRE (a.name() == newName);
  }
}
