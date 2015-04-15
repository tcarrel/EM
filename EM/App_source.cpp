#include "pch.h"

IFrameworkView^ App_source::CreateView(void)
{
  return ref new App();
}