#include "jseb2reader_plugin.h"
#include <daq_device_jseb2reader.h>

#include <strings.h>

int jseb2reader_plugin::create_device(deviceblock *db)
{

  //std::cout << __LINE__ << "  " << __FILE__ << "  " << db->argv0 << std::endl;
  // jseb2reader args (string partjseb, string dcm2device, string dcm2dat, string dcm2jseb, string outputfilename
  if ( strcasecmp(db->argv0,"device_jseb2reader") == 0 ) 
    {
      // we need at least 3 params
      if ( db->npar <4 ) return 1; // indicate wrong params
      
      int eventtype  = atoi ( db->argv1); // event type
      //int subid = atoi ( db->argv2); // subevent id
      
      // this is with eventtype,dcm2deviceName,dcm2datfileName,outputDataFileName, partjseb2name, dcm2jseb2name
      if ( db->npar ==4 )
	{
	  daq_device *x = new daq_device_jseb2reader( eventtype,
						    db->argv2,
						    db->argv3 );
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
 
      // this is with eventtype, partjseb2name, dcm2jseb2name,dcm2deviceName
      else if ( db->npar == 5 )
	{
	  daq_device *x = new daq_device_jseb2reader( eventtype,
						      db->argv2,
						    db->argv3,
						    db->argv4 );
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
 
      // this is with eventtype, subevt id, device_nr, slot nr, nr_modules
      // this is with eventtype, dcm2deviceName,dcm2datfileName,outputDataFileName, partjseb2name
      else if ( db->npar == 6 )
	{
	  daq_device *x = new daq_device_jseb2reader( eventtype,
						    db->argv2,
						    db->argv3,
						    db->argv4,
						    db->argv5 );
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
 
      // this is with eventtype, dcm2deviceName,dcm2datfileName,outputDataFileName, partjseb2name, dcm2jseb2name
      else if ( db->npar == 7 )
	{
	  daq_device *x = new daq_device_jseb2reader( eventtype,
						      db->argv2, // dcm2device
						      db->argv3, // dcm2dat
						      db->argv4, //  datafilename
						      db->argv5, //  partjseb2
						      db->argv6 ); // dcm2jseb2
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 

 // this is with eventtype,dcm2deviceName,dcm2datfileName,outputDataFileName, partjseb2name, dcm2jseb2name , nevents
      else if ( db->npar == 8 )
	{
	  daq_device *x = new daq_device_jseb2reader( eventtype,
						    db->argv2, // dcm2device
						    db->argv3, // dcm2dat
						    db->argv4, //  datafilename
						    db->argv5, //  partjseb2
						    db->argv6, // dcm2jseb2
						      atoi(db->argv7) ); // nevents
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
      return 1; // say "it is our device but the parameters ain't right"

    }
   return -1; // say " this is not our device"
}
  
void jseb2reader_plugin::identify(std::ostream& os, const int flag) const
{

  if ( flag <=2 )
    {
      os << " - JSEB2READER Plugin" << std::endl;
    }
  else
    {
      os << " - JSEB2READER Plugin, provides - " << std::endl;
      os << " -     device_jseb2reader (evttype, subid, device_nr [, slot, numberofmodules, l1_delay, nevents]) - readout a JSEB2READER device " 
	 << std::endl;

    }
      
}

jseb2reader_plugin _digip;

