#ifndef IR_RX_HASHER_HPP
#define IR_RX_HASHER_HPP

#include <stdint.h>

typedef void (*HasherCB_t)(uint32_t);

typedef enum {AUTO_MANUAL_IR, LEFT_IR, RIGHT_IR, UNKNOWN_IR} e_IR_signal_type;
e_IR_signal_type Check_IR_Type(uint32_t IR_num);

class Hasher
{

   /*
   This class forms a hash over the IR pulses generated by an
   IR remote.

   The remote key press is not converted into a code in the manner of
   the lirc module.  No attempt is made to decode the type of protocol
   used by the remote.  The hash is likely to be unique for different
   keys and different remotes but this is not guaranteed.

   This hashing process works for some remotes/protocols but not for
   others.  The only way to find out if it works for one or more of
   your remotes is to try it and see.
   */

   int mygpio, mytimeout;
   HasherCB_t mycallback;
   int in_code;
   uint32_t hash_val;
   int edges;
   uint32_t t1, t2, t3, t4;

   void _hash(int old_val, int new_val);
   void _callback(int gpio, int level, uint32_t tick);

   /* Need a static callback to link with C. */
   static void _callbackExt(int gpio, int level, uint32_t tick, void *user);

   public:

   Hasher(int gpio, HasherCB_t callback, int timeout=5);
};

#endif

