#ifndef __JSEB2READER_PLUGIN_H__
#define __JSEB2READER_PLUGIN_H__

#include <rcdaq_plugin.h>

#include <daq_device_jseb2reader.h>
#include <iostream>


class jseb2reader_plugin : public RCDAQPlugin {

 public:
  int  create_device(deviceblock *db);

  void identify(std::ostream& os = std::cout, const int flag=0) const;

};


#endif

