#ifndef _QB_NAMED_H
#define _QB_NAMED_H

#if defined(QB_RVALNAMED)
  #error QB_RVALNAMED define Error
#endif

#define QB_RVALNAMED const auto&&

#endif