%module rpdbtozypp
%{
#undef NORMAL
#include "pdbtozypp.h"
using namespace zypp;
%}

class PdbToZypp{
	public:
      //typedef zypp::ResStore ResStore;
		//PdbToZypp(zypp::ResStore  & _store);
		PdbToZypp();
      ~PdbToZypp();
      void readOut();
      ResStore getStore();
   private:
      ResStore store;
};
