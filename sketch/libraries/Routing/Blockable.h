#ifndef BLOACKABLE_H
#define BLOACKABLE_H

#include <Arduino.h>

/**
 * Base class for object which can need to be delayed without
 * blocking the whole activity (ie, blocked without using delay()).
 */
class Blockable
{
 private:
  /// Tells whether this object is blocked or not.
  bool _isBlocked;

  /// The time at which the object has been blocked.
  unsigned long _blockStart;

  /// The (minimal) number of milliseconds the object must remain blocked
  unsigned long _blockLen;

 protected:
  /**
   * Initializes an object whch can be blocked.
   */
  Blockable();

  /**
   * Tells what must be done when an object is blocked.
   * <p>Called by update()</p>
   *
   * <p>Anti-pattern, but no time to develop a Strategy pattern for this project now.</p>
   */
  virtual void onUpdate()=0;

 public:
  /**
   * Blocks the object for the number of milliseconds specified.
   * \millis the number of milliseconds the object must remain blocked.
   */
  void block(const unsigned long & blockLenMillis);

  /**
   * Blocks the object until unblock is called.
   */
  void block();

  /**
   * Unblocks an object.
   */
  void unblock();

  /**
   * Updates the state of an object.
   * <p>If the object is blocked with duration, checks the time out. Otherwise, calls onUpdate().</p>
   */
  void update();

  /**
   * Tells whether this object is blocked or not.
   * \return true if the object is blocked, false otherwise.
   */
  bool isBlocked()const;
};

#endif

