#include"pch.h"

#include"App_source.h"

IFrameworkView^ App_source::CreateView(void)
{
  return ref new App();
}