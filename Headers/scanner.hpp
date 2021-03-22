#include <vector>
#include <windows.h>
#include <map>
#include <iostream>

//-lpsapi => needs to be added to build cmd
class Scanner{
/*
Information/SampleCode for process memery handeling (in C#)
https://codingvision.net/c-how-to-scan-a-process-memory

Memory analysis cmd for debug console(VSC does not have memory view like VS)
-exec x/1w *hex-address*
Options: x/1w -> num means how many, letter means type (w=4byte, b=1byte)
Thats why memcpy could be used to interpret data in the desired data type
*/
    public:
        /*
        Used to determine what size the datatype has
        BYTE_X: used for whole numbers(inc. negative values)
        FPN: float(4bytes)
        DPFN: double(8bytes)
        */
        enum VALUETYPE{BYTE_1, BYTE_2, BYTE_4, BYTE_8, FPN, DFPN};

        //Singleton
        static Scanner& Instance();

        //Search in selected window for given value
        static std::vector<int*> FirstDataScan(HWND procID, VALUETYPE numberType,int number);
        //Search list of addresses if value is equals to new value
        static bool RescanAddressList(HWND selectedWinHndl, VALUETYPE numberType, int number, std::vector<int*> &aAddresses);
        //Create map with window handles and name
        static std::map<HWND, std::string> createWindowsList();
        

    private:
        //Variables
        std::map<HWND, std::string> m_listWinHndls; //Stores window handles

        //Functions
        //Singleton safety measures
        Scanner(){};
        Scanner(const Scanner&)=delete;

        //Functions regarding scanning/reading memory
        template<typename UNIT>
        static std::vector<int*> InitialValueScan(HWND selectedWindowHndl, int pValue);
        static void ReadAddressRange(const void* pAddr, SIZE_T pSize, int pValue, HANDLE pHdnl, std::vector<int*> &pAddresses);
        static void* incPtrByBytes(const void* adr, unsigned long long numOfBytes); //HelperFnct
        

        //Used to get some kind of process/window list
        static BOOL callbackEnumWindows(HWND hndl, LPARAM param);
        bool addWinHndlToList(HWND hndl);
};