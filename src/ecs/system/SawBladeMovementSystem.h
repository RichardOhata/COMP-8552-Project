//
// Created by richa on 2025-11-17.
//

#ifndef TEST_SAWBLADEMOVEMENTSYSTEM_H
#define TEST_SAWBLADEMOVEMENTSYSTEM_H

#include <cmath>
#include <vector>
#include <memory>
#include "Vector2D.h"
#include "Component.h"
#include "Entity.h"

class SawbladeMovementSystem {
public:
   void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) {
       const float TWO_PI = 2.0f * 3.14159265f;

       for (auto& e : entities) {
           if (!e->hasComponent<Transform>() || !e->hasComponent<SawbladePath>()) continue;

           auto& t = e->getComponent<Transform>();
           auto& path = e->getComponent<SawbladePath>();

           if (path.stationary) continue;
           Vector2D target;
           // Current coordinate waypoint the sawblade path is traveling to
           if (!path.waypoints.empty()) {
               target = path.waypoints[path.currentIndex];
           }


           // Check the type of motion (Linear or circular)
           switch (path.motionType) {
               // Linear Logic
               case SawbladeMotionType::Linear: {
                   Vector2D dir = (target - t.position).normalize();
                   t.position += dir * path.speed * dt;

                   // Check if reached target
                   bool reachedX = (dir.x >= 0 && t.position.x >= target.x) || (dir.x < 0 && t.position.x <= target.x);
                   bool reachedY = (dir.y >= 0 && t.position.y >= target.y) || (dir.y < 0 && t.position.y <= target.y);

                   if (reachedX && reachedY) {
                       t.position = Vector2D{t.position.x, t.position.y};

                       // Apply action for this waypoint
                       if (path.currentIndex < path.actions.size() && path.actions.size() > 1) {

                           const auto& act = path.actions[path.currentIndex];
                           if (act.switchToCircular) {
                               path.motionType = SawbladeMotionType::Circular;
                               path.center = t.position;
                               path.radius = act.radius;
                               path.angularSpeed = act.angularSpeed;
                               path.clockwise = act.clockwise;
                               path.angle = 0.0f;
                               path.rotationAcc = 0.0f;
                               break;
                           }
                       }

                       if (path.motionType == SawbladeMotionType::Linear) {
                           path.currentIndex = (path.currentIndex + 1) % path.waypoints.size();
                       }
                   }
                   break;
               }

               case SawbladeMotionType::Circular: {
                   float direction = path.clockwise ? -1.0f : 1.0f;
                   float deltaAngle = direction * path.angularSpeed * dt;
                   path.angle += deltaAngle;
                   path.rotationAcc += std::abs(deltaAngle);

                   // Contain angle in [0, 2π)
                   if (path.angle >= TWO_PI) path.angle -= TWO_PI;
                   if (path.angle < 0) path.angle += TWO_PI;

                   t.position.x = path.center.x + path.radius * std::cos(path.angle);
                   t.position.y = path.center.y + path.radius * std::sin(path.angle);

                   // Completed circle rotation
                   if (path.rotationAcc >= TWO_PI && path.actions.size() > 1) {
                       path.rotationAcc = 0.0f;
                       Vector2D target = path.waypoints[path.currentIndex];
                       Vector2D start = path.center;
                       Vector2D diff = target - start;
                       float dist = diff.length();
                       if (dist < 0.1f) {
                           t.position = target;
                           path.currentIndex = (path.currentIndex + 1) % path.waypoints.size();
                       } else {
                           Vector2D dir = diff.normalize();
                           t.position += dir * path.speed * dt;

                       }

                       // t.position = path.waypoints[path.currentIndex];

                       // Advance to next waypoint
                       // path.currentIndex = (path.currentIndex + 1) % path.waypoints.size();
                       // Apply next action
                       if (path.currentIndex < path.actions.size()) {
                           const auto& act = path.actions[path.currentIndex];
                           if (act.switchToLinear) {
                               path.motionType = SawbladeMotionType::Linear;
                           } else if (act.switchToCircular) {
                               path.motionType = SawbladeMotionType::Circular;
                               path.center = path.waypoints[path.currentIndex];
                               path.radius = act.radius;
                               path.angularSpeed = act.angularSpeed;
                               path.clockwise = act.clockwise;
                               path.angle = 0.0f;
                               path.rotationAcc = 0.0f;
                           }
                       }

                   }
                   //
                   break;
               }
           }
       }
   }


};

#endif //TEST_SAWBLADEMOVEMENTSYSTEM_H