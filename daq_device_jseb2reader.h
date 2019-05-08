#ifndef __DAQ_DEVICE_JSEB2READER_H__
#define __DAQ_DEVICE_JSEB2READER_H__




#include <stdio.h>


#include <daq_device.h>
#include <jseb2readerTriggerHandler.h>
#include <iostream>
#include <string>

//nclude "jseb2reader_lib.h"


class daq_device_jseb2reader : public  daq_device {

public:

  daq_device_jseb2reader (const int eventtype
			  , const string & dcm2devicename = "DCMGROUP.FVTX.1"
			  , const string & dcm2datfileName = "dcm2FvtxPar.dat"
			  , const string & outputDataFileName = "rcdaq_fvtxdata.prdf"
			  ,const string & dcm2partreadoutJsebName = "JSEB2.8.0"
			  , const string & dcm2Jseb2Name = "JSEB2.5.0"
			  , const int nevents = 0);
  
  ~daq_device_jseb2reader();


  void identify(std::ostream& os = std::cout) const;

  int max_length(const int etype) const;

  // functions to do the work

  int put_data(const int etype, int * adr, const int length);

  int init();
  int endrun();

  int rearm( const int etype);

protected:
  subevtdata_ptr sevt;
  unsigned int number_of_words;
  string _dcm2jseb2name;
  string partreadoutJseb2Name;
  string dcm2configfilename; // dcm2 dat file
  string dcm2name;
  string _outputDataFileName;
 
  int _nevents;
  //  std::string _dcmhost;
  // std::string _configfile;

  int _broken;

  jseb2readerTriggerHandler *_th;


};

#endif

