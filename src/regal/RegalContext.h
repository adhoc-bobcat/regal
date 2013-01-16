/* NOTE: Do not edit this file, it is generated by a script:
   Export.py --api gl 4.2 --api wgl 4.0 --api glx 4.0 --api cgl 1.4 --api egl 1.0 --outdir .
*/

/*
  Copyright (c) 2011 NVIDIA Corporation
  Copyright (c) 2011-2012 Cass Everitt
  Copyright (c) 2012 Scott Nations
  Copyright (c) 2012 Mathias Schott
  Copyright (c) 2012 Nigel Stewart
  Copyright (c) 2012 Google Inc.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
  Intended formatting conventions:
  $ astyle --style=allman --indent=spaces=2 --indent-switches
*/

#ifndef __REGAL_CONTEXT_H__
#define __REGAL_CONTEXT_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include "RegalThread.h"
#include "RegalPrivate.h"
#include "RegalDispatcher.h"
#include "RegalDispatchError.h"
#include "RegalSharedList.h"

#if REGAL_SYS_PPAPI
#define __gl2_h_  // HACK - revisit
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/ppb_opengles2.h>
#endif

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

struct DebugInfo;
struct ContextInfo;

struct Marker;
struct Frame;
#if REGAL_EMULATION
struct RegalObj;
struct RegalPpa;
namespace Emu { struct Ppca; };
struct RegalBin;
struct RegalDsa;
namespace Emu { struct Iff; };
namespace Emu { struct So; };
struct RegalVao;
namespace Emu { struct TexC; };
#endif

struct RegalContext
{
  RegalContext();
  ~RegalContext();

  void Init();

  bool                initialized;
  Dispatcher          dispatcher;
  DispatchErrorState  err;
  DebugInfo          *dbg;
  ContextInfo        *info;

  //
  // Emulation
  //

  Marker             *marker;
  Frame              *frame;
#if REGAL_EMULATION
  // Fixed function emulation
  int emuLevel;
  RegalObj           *obj;
  RegalPpa           *ppa;
  Emu::Ppca          *ppca;
  RegalBin           *bin;
  RegalDsa           *dsa;
  Emu::Iff           *iff;
  Emu::So            *so;
  RegalVao           *vao;
  Emu::TexC          *texc;
#endif

  #if REGAL_SYS_PPAPI
  PPB_OpenGLES2      *ppapiES2;
  PP_Resource         ppapiResource;
  #endif

  RegalSystemContext  sysCtx;
  Thread::Thread      thread;

  GLLOGPROCREGAL      logCallback;

  //
  // Regal context sharing
  //

  shared_list<RegalContext *> shareGroup;

  // Query that any of the contexts in the share
  // group are already initialized

  bool groupInitialized() const;

  // Get any context in the share group that is
  // already initialized

  RegalContext *groupInitializedContext();

  // State tracked via EmuContextState.py / Regal.cpp

  size_t              depthBeginEnd;   // Normally zero or one
  size_t              depthPushAttrib; //

  // For RegalDispatchCode

  size_t              codeInputNext;
  size_t              codeOutputNext;
};

REGAL_NAMESPACE_END

#endif // __REGAL_CONTEXT_H__
