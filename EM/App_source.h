#ifndef _APP_SOURCE_H
#define _APP_SOURCE_H

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

// The class the creates the instance of the core framework class.
ref class App_source sealed : IFrameworkViewSource
{
public:
  virtual IFrameworkView^ CreateView(void);
};
#endif