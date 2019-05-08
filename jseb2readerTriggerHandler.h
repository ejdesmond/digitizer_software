#ifndef __JSEB2READERTRIGGERHANDLER_H__
#define __JSEB2READERTRIGGERHANDLER_H__

#include <string>

#include "TriggerHandler.h"



#include "wdc_defs.h"
#include "wdc_lib.h"
#include "utils.h"
#include "status_strings.h"
#include "samples/shared/diag_lib.h"
#include "samples/shared/wdc_diag_lib.h"
#include "pci_regs.h"
#include "wizard/my_projects/jseb2_lib.h"
#include "adcj.h"
//#include "rcdaqController.h"
#include "jseb2Controller.h"
#include "dcm2Impl.h"

#include <Dcm2_FileBuffer.h>



#define VENDORID 0x1172
#define DEVICEID 0x4


class Eventiterator;

class jseb2readerTriggerHandler : public TriggerHandler {

public:

  jseb2readerTriggerHandler(  const int eventtype
			    , const string & dcm2datfileName = "dcm2FvtxPar.dat"
			    , const string & outputDataFileName = "rcdaq_fvtxdata.prdf"
			    ,const string & dcm2partreadoutJsebName = "JSEB2.8.0"
			    , const string & dcm2Jseb2Name = "JSEB2.5.0"
			    , const string & adcJseb2Name = "JSEB2.5.0"
			    , const int slot_nr = 16
			    , const int nr_modules = 3
			    , const int l1_delay = 48
			    , const int n_samples = 31
			    , const int nevents = 0);

  ~jseb2readerTriggerHandler(); 


  //  virtual void identify(std::ostream& os = std::cout) const = 0;

  // this is the virtual worker routine
  int wait_for_trigger( const int moreinfo=0);
  int initialize();
  int init();
  int endrun();
  int parseDcm2Configfile(string dcm2datfilename);
  int put_data( int *d, const int max_words);
  int get_status() const {return _broken;};
  bool dcm2_getline(ifstream *fin, string *line);
 int rearm();

 protected:



  int _broken;

  int get_buffer();  // read the next buffer and parse it
  ADC * padc;
  jseb2Controller * pjseb2c;
  unsigned long _nevents;
  string dcm2jseb2name;
  string _adcJseb2Name;
  dcm2Impl *pdcm2Object;
  string partreadoutJseb2Name;
  string dcm2configfilename; // dcm2 dat file
  string dcm2name;
  string _outputDataFileName;
  string datafiledirectory;
  pthread_t dcm2_tid;
  bool enable_rearm;
  
  int _slot_nr;
  int _nr_modules;
  int _l1_delay;
  int _n_samples;
  

  WD_PCI_SLOT thePCISlot;
  WDC_DEVICE_HANDLE _theHandle;

  unsigned int _evt_count;
  unsigned int _current_event;
  bool debugReadout;
  //  static WDC_DEVICE_HANDLE hPlx;
  //static PLX_DMA_HANDLE hDMA;

  //static UINT32 *buffer;

};

#endif
