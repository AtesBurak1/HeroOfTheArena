#ifndef LEAF_ARCHER_HPP
#define LEAF_ARCHER_HPP

#include "HOTA/Hero.hpp"
#include "HOTA/Animation.hpp"
#include <string>

class LeafArcher : public Hero
{
private:
  void init_var();
  void init_ani();
  void init_ani_stats();
  void init_stats();

  /**
   * atk2 -> hit_entangle
   * atk3 -> shower_effect
   */

public:
  LeafArcher();
  ~LeafArcher();
  void skill();
  void upgrade();
  void update();
  void render(sf::RenderTarget &target);
  void move_character();
};

#endif
