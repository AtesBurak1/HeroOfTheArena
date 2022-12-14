#include "HOTA/Physics.hpp"
#include <iostream>

Physics::Physics(std::string path, int character_actual_width, int character_actual_height)
    : AnimationCreator{path},
      velocity_x{5.f}, velocity_y{7.5f}, gravity{10.f},
      character_actual_width{character_actual_width}, character_actual_height{character_actual_height},
      top_point{250.f}, is_reach_to_top_point{false}
{
}

Physics::~Physics()
{
}

void Physics::init_position()
{
  this->position = this->initial_positions;
}

void Physics::projectile_jump(sf::Keyboard::Key Key, std::string &jump_ani_name)
{
  this->velocity_x = 4.f;
  this->jump(jump_ani_name);
  this->move_left_right(Key);
  this->velocity_x = 5.f;
}

void Physics::move_left_right(sf::Keyboard::Key Key)
{
  if (Key == sf::Keyboard::D) // Right
  {
    return this->move_right();
  }
  if (Key == sf::Keyboard::A) // Left
  {
    return this->move_left();
  }
}

void Physics::move_right()
{
  if (this->position.x < this->window_width - this->character_width * 0.5 - this->character_actual_width)
  {
    this->set_position(sf::Vector2f{this->position.x + this->velocity_x, this->position.y});
  }
}

void Physics::move_left()
{
  if (this->position.x > (this->character_width * 0.5 - this->character_actual_width) * -1)
  {
    this->set_position(sf::Vector2f{this->position.x - this->velocity_x, this->position.y});
  }
}

void Physics::jump(std::string &jump_ani_name)
{
  this->jump_up(jump_ani_name);
  this->jump_down(jump_ani_name);
}

void Physics::jump_up(std::string &jump_ani_name)
{
  if (this->is_reach_to_top_point)
  {
    return;
  }
  this->velocity_y -= 0.2;
  if (this->position.y < this->top_point) // reach top point
  {
    this->is_reach_to_top_point = true;
    if (jump_ani_name == "jump_projectile_up")
    {
      jump_ani_name = "jump_projectile_down";
    }
    else
    {
      jump_ani_name = "jump_down";
    }
  }
  this->set_position(sf::Vector2f{this->position.x, this->position.y - this->velocity_y});
}

void Physics::jump_down(std::string &jump_ani_name)
{
  if (!this->is_reach_to_top_point)
  {
    return;
  }
  this->velocity_y += 0.2;
  if (this->position.y > this->initial_positions.y - 10) // came back to ground
  {
    this->is_reach_to_top_point = false;
    jump_ani_name = "idle";
    this->velocity_y = 7.5f;
  }
  this->set_position(sf::Vector2f{this->position.x, this->position.y + this->velocity_y});
}

void Physics::set_position(sf::Vector2f new_position)
{
  this->position = new_position;
  this->set_all_animation_position(this->position);
}

bool Physics::is_collide(Physics *obj)
{
  if (this->position.x > (obj->position.x - (obj->character_actual_width + this->character_actual_width)))
  {
    return true;
  }
  return false;
}
