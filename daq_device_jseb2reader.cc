#include "daq_device_jseb2reader.h"

#include <unistd.h>
#include <string.h>

#include <signal.h>
#include <iostream>

#define IDHBD_FPGASHORT       1222


using namespace std;

daq_device_jseb2reader::daq_device_jseb2reader(const int eventtype
					   , const string & dcm2devicename
					   , const string & dcm2datfileName
					   , const string & outputDataFileName
					   ,const string & dcm2partreadoutJsebName
					   , const string & dcm2Jseb2Name
					   , const int nevents)
{

  m_eventType  = eventtype;
  partreadoutJseb2Name = dcm2partreadoutJsebName;
  dcm2name = dcm2devicename; // dcmgroup name from dat file
  _dcm2jseb2name = dcm2Jseb2Name;
  dcm2configfilename = dcm2datfileName;
  _outputDataFileName = outputDataFileName;
  _nevents  = nevents;

  _th = 0;

  _broken = 0;


  cout << __LINE__ << "  " << __FILE__ << " registering triggerhandler " << endl;
  _th  = new jseb2readerTriggerHandler ( m_eventType,dcm2configfilename,dcm2name,_outputDataFileName,partreadoutJseb2Name,_dcm2jseb2name ,_nevents);
  _broken = _th->get_status();
  registerTriggerHandler ( _th);

}


/*
 * init
 * returns 0 on success ; non-zero on failure
 */
int  daq_device_jseb2reader::init()
{
  int status = 0;
  if ( _th) 
    status = _th->init();

  return status;
}








daq_device_jseb2reader::~daq_device_jseb2reader()
{
  /*
  if ( _th) 
    {
      clearTriggerHandler();
      delete _th;
      _th = 0;
    }
  */
}



// the put_data function

/**
 * put_data
 * When this function is called data is determined to be ready. So read the data
 */
int daq_device_jseb2reader::put_data(const int etype, int * adr, const int length )
{
  //cout << __FILE__ << "  " << __LINE__ << " put_data etype= " << etype  << " length= " << length << endl;

  if ( _broken ) 
    {
      cout << __LINE__ << "  " << __FILE__ << " broken ";
      identify();
      return 0; //  we had a catastrophic failure
    }

  if ( ! _th) return 0;  // if we don't have a trigger object, we are not reading anything right now

  if (etype != m_eventType )  // not our id
    {
      return 0;
    }

  // PRDFEVENT == 1
  if (!  daq_getEventFormat() ) 
    {
      return 0;  // we only do prdf and don't do anything for now if not
    }
  
  /*
  sevt =  (subevtdata_ptr) adr;
  // set the initial subevent length
  sevt->sub_length =  SEVTHEADERLENGTH;

  // update id's etc
  sevt->sub_id =  m_subeventid;
  sevt->sub_type=4;
  sevt->sub_decoding = ID4EVT;
  sevt->reserved[0] = 0;
  sevt->reserved[1] = 0;
      
  
  int  *d = (int *) &sevt->data;
  
  int len = length - SEVTHEADERLENGTH -1;
  */
  int len;
  len = _th->put_data(adr, length ); // if not using header
  /*
  len = _th->put_data(d, len );
  sevt->sub_padding = len%2;
  len = len + (len%2);
  sevt->sub_length += len;
  
  return  sevt->sub_length;
  */
  //cout << __FILE__ << "  " << __LINE__ << " put_data: returning data read = " << len << endl;
  return len;
}


void daq_device_jseb2reader::identify(std::ostream& os) const
{
  
  os  << "JSEB2READER Device  Event Type: " << m_eventType << " partition Jseb2 " << partreadoutJseb2Name.c_str();

  if ( _th) os << " **trigger ";
  if ( _broken) os << " ** not functional ** " << _broken;
  os << endl;

}

int daq_device_jseb2reader::max_length(const int etype) const
{
  if (etype != m_eventType) return 0;
  //return  (_nr_modules * 40 * 12 + 10 + 8);
  return (5989); // (5997); // (5998); // max size of event from jseb2reader
}

int  daq_device_jseb2reader::endrun()
{
  if ( _th) _th->endrun();
  return 0;
}

// the rearm() function
int  daq_device_jseb2reader::rearm(const int etype)
{
  if (etype != m_eventType) return 0;
  return 0;
}


