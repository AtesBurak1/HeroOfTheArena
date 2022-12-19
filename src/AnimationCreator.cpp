#include "HOTA/AnimationCreator.hpp"
#include <iostream>

AnimationCreator::AnimationCreator() : AnimationCreator{""}
{
}

AnimationCreator::AnimationCreator(const std::string &path) : path{path}, animation{nullptr}, window_width{1536}, window_height{768}
{
  this->idle_num = 0;
  this->atk_one_num = 0;
  this->atk_two_num = 0;
  this->atk_sp_num = 0;
  this->run_num = 0;
  this->roll_num = 0;
  this->jump_num = 0;
  this->defend_num = 0;
  this->death_num = 0;
  this->take_dmg_num = 0;
  this->jump_up_num = 0;
  this->jump_down_num = 0;
}

AnimationCreator::~AnimationCreator()
{
  for (auto &&i : this->all_animations)
  {
    delete i.second;
  }
}

void AnimationCreator::insert_new_animation(const std::string &animation_name, const std::string &png_name, const size_t &animation_len, const bool &is_repeat)
{
  this->all_animations.insert(std::pair<std::string, Animation *>(animation_name, new Animation{this->path, animation_name, png_name, animation_len, is_repeat}));
}

void AnimationCreator::set_and_calculate_position()
{
  this->animation = this->all_animations["idle"];
  this->calculate_inital_position();
  this->set_all_animation_position(this->initial_positions);
}

void AnimationCreator::select_animation(const std::string &animation_name)
{
  if (this->select_jump_animation(animation_name))
  {
    return;
  }
  for (auto &&i : this->all_animations)
  {
    if (i.first == animation_name)
    {
      this->animation = i.second;
      return;
    }
  }
  this->animation = this->all_animations["idle"];
}

bool AnimationCreator::select_jump_animation(const std::string &animation_name)
{
  if (animation_name == "jump_projectile_up")
  {
    this->animation = this->all_animations["jump_up"];
    return true;
  }
  if (animation_name == "jump_projectile_down")
  {
    this->animation = this->all_animations["jump_down"];
    return true;
  }
  if (animation_name == "jump_projectile_up_left")
  {
    this->animation = this->all_animations["jump_up_left"];
    return true;
  }
  if (animation_name == "jump_projectile_down_left")
  {
    this->animation = this->all_animations["jump_down_left"];
    return true;
  }
  return false;
}

void AnimationCreator::set_all_animation_position(const sf::Vector2f &last_position)
{
  for (auto &&i : this->all_animations)
  {
    this->set_animation_position(i.second, last_position);
  }
}

void AnimationCreator::set_animation_position(Animation *animation, const sf::Vector2f &last_position)
{
  for (auto &&i : *animation->get_sprite())
  {
    i->setPosition(last_position);
  }
}

void AnimationCreator::calculate_inital_position()
{
  this->initial_positions.y = this->window_height - this->character_height - 35; // ground height is 35
}