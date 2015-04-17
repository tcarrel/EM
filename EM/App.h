#ifndef _APP_H
#define _APP_H

#include"Game.h"

#include"pch.h"

// Use common namespaces
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;

ref class App sealed : public IFrameworkView
{
  bool window_closed_;
  CGame game_;

public:
  // Functions called by Windows
  virtual void Initialize(CoreApplicationView^);
  virtual void SetWindow(CoreWindow^);
  virtual void Load(String^);
  virtual void Run(void);
  virtual void Uninitialize(void);

  //  Event that is called when window is ready to be activated
  void On_activated(CoreApplicationView^, IActivatedEventArgs^);

  void pointer_pressed(CoreWindow^, PointerEventArgs^ );
  void key_down(CoreWindow^, KeyEventArgs^);
  void key_up(CoreWindow^, KeyEventArgs^);

  void suspending(Object^, SuspendingEventArgs^);
  void resuming(Object^, Object^);
  void closed(CoreWindow^, CoreWindowEventArgs^);

};
#endif