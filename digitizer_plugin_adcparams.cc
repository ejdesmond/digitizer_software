#include "digitizer_plugin.h"
#include <daq_device_digitizer.h>

 

#include <strings.h>

int digitizer_plugin::create_device(deviceblock *db)
{
 // jseb2reader args (string partjseb, string dcm2device, string dcm2dat, string dcm2jseb, string outputfilename
  std::cout << __LINE__ << "  " << __FILE__ << " num params =  " << db->npar << " " << db->argv0 << std::endl;
  int sub_id = 0; // not used ; here only for backward compatibility

  if ( strcasecmp(db->argv0,"device_digitizer") == 0 ) 
    {
      // we need at least 3 params
      if ( db->npar <4 ) return 1; // indicate wrong params
      
      int eventtype  = atoi ( db->argv1); // event type
      
      
      // this is with eventtype, dcm2deviceName,dcm2datfileName
      // defaults par_jseb, dm2_jseb, slot_nr = 16, nr_modules = 3 , li_delay = 58, nevents = 0
      if ( db->npar == 4 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3 );// dcm2dat
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
      //rcdaq_client create_device device_jseb2reader 1 "DCMGROUP.FVTX.1" "dcm2FvtxPar.dat" "rcdaq_fvtxdata.prdf" "JSEB2.8.0" "JSEB2.5.0" 0
      // this is with eventtype, "DCMGROUP.FVTX.1" "dcm2FvtxPar.dat" "rcdaq_fvtxdata.prdf"
      // defaults dm2 jseb, slot_nr = 16, nr_modules = 3 , li_delay = 58, nevents = 0
      // for multi xmit groups the arguement lis is changed to:
      // eventtype, subeventid, partreadoutjseb2name,dcm2jseb2name,adcjseb2name, nevents, nxmitgroups, slot_nr, nr_modules, l1_delay, nsamples [slot_nr, nr_modules, l1_delay, nsamples]
      else if ( db->npar == 5 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3,// dcm2dat
						    db->argv4 ); // part_jseb
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
 //rcdaq_client create_device device_jseb2reader 1 "DCMGROUP.FVTX.1" "dcm2FvtxPar.dat" "rcdaq_fvtxdata.prdf" "JSEB2.8.0" 
      // this is with eventtype, "DCMGROUP.FVTX.1" "dcm2FvtxPar.dat"  "JSEB2.8.0" 0
      // defaults dcm2_jseb, slot_nr = 16, nr_modules = 3 , li_delay = 58, nevents = 0
      else if ( db->npar == 6 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3,// dcm2dat
						    db->argv4,//  partjseb2
						    db->argv5 );// dcm2jseb2
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
 
      // this is with eventtype, "DCMGROUP.FVTX.1" "dcm2FvtxPar.dat" "rcdaq_fvtxdata.prdf" "JSEB2.8.0" "JSEB2.5.0" 
      // defaults: nr_modules = 3, li_delay = 58, nevents = 0
      else if ( db->npar == 7 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3,// dcm2dat
						    db->argv4,//  partjseb2
						    db->argv5,//  dcm2jseb2
						    db->argv6 ); // adcjseb2
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
      //  here an output file name is defaulted
 // eventtype, subid, dcm2datfileName,partjseb2name, dcm2jseb2name adcjseb2Name nevents, nxmitgroups ,slot nr, nr_modules, l1_delay, nsamples
      // no num modules , l1_delay
      // defaults l1_delay = 58, nevents = 0
      else if ( db->npar == 8 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3,// dcm2dat
						    db->argv4,//  partjseb2
						    db->argv5,//  dcm2jseb2
						    db->argv6,//  adcjseb2
						    atoi(db->argv7) );// nevents
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
      //eventtype, subid,dcm2datfileName ,partjseb2name, dcm2jseb2name adcjseb2name nevents, nxmitgroups, slot nr, nr_modules, l1_delay, nsamples 
      // default nevents = 0
 else if ( db->npar == 9 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3,// dcm2dat
						    db->argv4,//  partjseb2
						    db->argv5,//  dcm2jseb2
						    db->argv6,// adcjseb2
						    atoi(db->argv7), // nevents
						    atoi(db->argv8) );// num_xmitgroups
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
      //eventtype, subid dcm2datfileName,partjseb2name, dcm2jseb2name , adcjseb2name, nevents, nxmitgroups, slot nr, nr_modules, l1_delay, nsamples
      // leaves out output file name
else if ( db->npar == 10 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3,// dcm2dat
						    db->argv4,//  partjseb2
						    db->argv5,//  dcm2jseb2
						    db->argv6,// adcjseb2
						    atoi(db->argv7), // nevents
						    atoi(db->argv8), // num_xmitgroups
						    atoi(db->argv9) );// slot_nr
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	}
 else if ( db->npar == 11 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3,// dcm2dat
						    db->argv4,//  partjseb2
						    db->argv5,//  dcm2jseb2
						    db->argv6,// adcjseb2
						    atoi(db->argv7), // nevents
						    atoi(db->argv8), // num_xmitgroups
						    atoi(db->argv9), // slot_nr
						    atoi(db->argv10) );// num_modules
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
else if ( db->npar == 12 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3,// dcm2dat
						    db->argv4,//  partjseb2
						    db->argv5,//  dcm2jseb2
						    db->argv6,// adcjseb2
						    atoi(db->argv7), // nevents
						    atoi(db->argv8), // num_xmitgroups
						    atoi(db->argv9), // slot_nr
						    atoi(db->argv10), // num_modules
						    atoi(db->argv11) );// l1_delay
	  
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
else if ( db->npar == 13 )
	{
	  daq_device *x = new daq_device_digitizer( eventtype,
						    sub_id,
						    db->argv3,// dcm2dat
						    db->argv4,//  partjseb2
						    db->argv5,//  dcm2jseb2
						    db->argv6,// adcjseb2
						    atoi(db->argv7), // nevents
						    atoi(db->argv8), // num_xmitgroups
						    atoi(db->argv9), // slot_nr
						    atoi(db->argv10), // num_modules
						    atoi(db->argv11), // l1_delay
						    atoi(db->argv12) );// n_samples
	  
	  x->identify();
	  
	  add_readoutdevice (x);
	  return 0;  // say "we handled this request" 
	} 
      // TODO: for a second xmit group 4 more arguement options are needed to specify slot, nmodules, l1 delay and n_samples
      // TODO: at leas 2 more are needed for slot and n modules if l1_delay and n_samples is constant
      return 1; // say "it is our device but the parameters ain't right"

    }
   return -1; // say " this is not our device"
} // create_device
  
void digitizer_plugin::identify(std::ostream& os, const int flag) const
{

  if ( flag <=2 )
    {
      os << " - DIGITIZER Plugin" << std::endl;
    }
  else
    {
      os << " - DIGITIZER Plugin, provides - " << std::endl;
      os << " -     device_digitizer (evttype, subid, device_nr [, slot, numberofmodules, l1_delay, nevents]) - readout a DIGITIZER device " 
	 << std::endl;

    }
      
}

digitizer_plugin _digip;

