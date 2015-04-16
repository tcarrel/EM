#include "pch.h"

void make_dialog(String^, String^);

void App::Initialize(CoreApplicationView^ AppView)
{
  window_closed_ = false;

  // Set OnActivated function to handle to Activated "event"
  AppView->Activated += ref new TypedEventHandler
    <CoreApplicationView^, IActivatedEventArgs^>(this, &App::On_activated);

  CoreApplication::Suspending +=
    ref new EventHandler<SuspendingEventArgs^>(this, &App::suspending);

  CoreApplication::Resuming +=
    ref new EventHandler<Object^>(this, &App::resuming);
}

void App::SetWindow(CoreWindow^ window) 
{
  window->PointerPressed += ref new TypedEventHandler
    <CoreWindow^, PointerEventArgs^>(this, &App::pointer_pressed);

  window->KeyDown += ref new TypedEventHandler
    <CoreWindow^, KeyEventArgs^>(this, &App::key_down);

  window->KeyUp += ref new TypedEventHandler
    <CoreWindow^, KeyEventArgs^>(this, &App::key_up);

  window->Closed += ref new TypedEventHandler
    <CoreWindow^, CoreWindowEventArgs^>(this, &App::closed);
}

void App::Load(String^ EntryPoint)
{}

void App::Run( void ) 
{
  game_.initialize();

  // Get window ptr.
  CoreWindow^ Window = CoreWindow::GetForCurrentThread();

  // Dispatch events.
  while (!window_closed_)
  {
    Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

   //Run the game
    game_.update();
    game_.render();
  }
}

void App::Uninitialize( void ) 
{}

void App::On_activated(CoreApplicationView^ core_app_view, IActivatedEventArgs^ args)
{
  CoreWindow^ Window = CoreWindow::GetForCurrentThread();
  Window->Activate();
}

void App::pointer_pressed(CoreWindow^ window, PointerEventArgs^ args)
{
  MessageDialog dialog("Thank you for noticing this notice.", "Notice!");
  dialog.ShowAsync();
}
void App::key_down(CoreWindow^ window, KeyEventArgs^ args)
{
  switch (args->VirtualKey)
  {
  case VirtualKey::A:
    make_dialog("Key pressed", "A");
    break;
  case VirtualKey::D:
    make_dialog("Key pressed", "D");
    break;
  case VirtualKey::S:
    make_dialog("Key pressed", "S");
    break;
  case VirtualKey::W:
    make_dialog("Key pressed", "W");
    break;
  default:
    ;
  }
}
void App::key_up(CoreWindow^ window, KeyEventArgs^ args)
{
}

void App::suspending(Object^ sender, SuspendingEventArgs^ args)
{
}
void App::resuming(Object^ sender, Object^ args)
{
}
void App::closed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
  window_closed_ = true;
}

void make_dialog(String^ text, String^ heading)
{
  MessageDialog dialog(text, heading);
  dialog.ShowAsync();
}