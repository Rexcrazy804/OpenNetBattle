#pragma once
#include <Thor/Animations.hpp>
using thor::FrameAnimation;
using thor::AnimationMap;
using sf::IntRect;

#include "bnEntity.h"
#include "bnMobState.h"
#include "bnTextureType.h"
#include "bnMobHealthUI.h"
#include "bnAnimationComponent.h"

class ProgsMan : public Entity {
public:
  ProgsMan(void);
  virtual ~ProgsMan(void);

  virtual void Update(float _elapsed);
  virtual bool Move(Direction _direction);
  virtual void RefreshTexture();
  virtual vector<Drawable*> GetMiscComponents();
  virtual int GetStateFromString(string _string);
  virtual int GetHealth() const;
  virtual TextureType GetTextureType() const;

  MobState GetMobState() const;
  void SetHealth(int _health);
  int Hit(int _damage);
  float GetHitHeight() const;
  int* ProgsMan::getAnimOffset();
  void Attack();

  void SetTarget(Entity*);

private:
  //Old static
  float blinker;
  float x1, y1, x2, y2;
  sf::Clock clock;

  //Cooldowns
  float cooldown;
  float attackCooldown;
  float waitCooldown;

  //Animation
  float explosionProgress;
  float explosionProgress2;
  float attackDelay;
  Sprite explosion;
  Sprite explosion2;
  FrameAnimation explode;

  AnimationComponent animationComponent;

  float hitHeight;
  Direction direction;
  MobState state;
  TextureType textureType;
  MobHealthUI* healthUI;
  AnimationMap<Sprite, MobState> animator;
  sf::Shader whiteout;

  // AI
  Entity* target;
};