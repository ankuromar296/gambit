//#
//# FILE: gsmincl.cc   miscellaneous GSM functions
//#
//# $Id$
//#

#include "gsmincl.h"
#include "string.h"


bool PortionSpecMatch( const PortionSpec& t1, const PortionSpec& t2 )
{
  if( t1 == t2 )
    return true;
  else if((t1.ListDepth == t2.ListDepth) &&
	  (((t1.Type & porMIXED  ) && (t2.Type & porMIXED  )) ||
	   ((t1.Type & porBEHAV  ) && (t2.Type & porBEHAV  )) ||
	   ((t1.Type & porOUTCOME) && (t2.Type & porOUTCOME)) ||
	   ((t1.Type & porNFG    ) && (t2.Type & porNFG    )) ||
	   ((t1.Type & porEFG    ) && (t2.Type & porEFG    ))))
    return true;
  else
    return false;
}





struct PortionSpecTextType
{
  unsigned long Type;
  char* Text;
};  


#define NumPortionSpecs 35

PortionSpecTextType _PortionSpecText[] =
{
  { porERROR,            "ERROR" },
  
  { porBOOL,             "BOOLEAN" },
  { porFLOAT,            "FLOAT" },
  { porINTEGER,          "INTEGER" },
  { porRATIONAL,         "RATIONAL" },
  { porTEXT,             "TEXT" },
  { porNFG_FLOAT,        "NFG(FLOAT)" },
  { porNFG_RATIONAL,     "NFG(RATIONAL)" },
  { porEFG_FLOAT,        "EFG(FLOAT)" },
  { porEFG_RATIONAL,     "EFG(RATIONAL)" },
  { porMIXED_FLOAT,      "MIXED(FLOAT)" },
  { porMIXED_RATIONAL,   "MIXED(RATIONAL)" },
  { porBEHAV_FLOAT,      "BEHAV(FLOAT)" },
  { porBEHAV_RATIONAL,   "BEHAV(RATIONAL)" },

  { porOUTCOME_FLOAT,    "OUTCOME(FLOAT)" },
  { porOUTCOME_RATIONAL, "OUTCOME(RATIONAL)" },
  { porPLAYER_NFG,       "NFPLAYER" },
  { porPLAYER_EFG,       "EFPLAYER" },
  { porNF_SUPPORT,       "NFSUPPORT" },
  { porEF_SUPPORT,       "EFSUPPORT" },
  { porINFOSET,          "INFOSET" },
  { porNODE,             "NODE" },
  { porACTION,           "ACTION" },
  { porSTRATEGY,         "STRATEGY" },

  { porREFERENCE,        "REFERENCE" },

  { porOUTPUT,           "OUTPUT" },
  { porINPUT,            "INPUT" },

  { porNULL,             "NULL" },

  { porUNDEFINED,        "UNDEFINED" },

  { porNFG,              "NFG" },
  { porEFG,              "EFG" },
  { porMIXED,            "MIXED" },
  { porBEHAV,            "BEHAV" },
  { porOUTCOME,          "OUTCOME" },

  { porANYTYPE,          "ANYTYPE" }
};


gString PortionSpecToText(const PortionSpec& spec)
{
  int i;
  gString result;
  for(i=0; i<NumPortionSpecs; i++)
    if(spec.Type == _PortionSpecText[i].Type)
      if(result == "")
	result = _PortionSpecText[i].Text;
      else
	result = result + " " + _PortionSpecText[i].Text;

  if(result == "")
    for(i=0; i<NumPortionSpecs-6; i++)
      if(spec.Type & _PortionSpecText[i].Type)
	if(result == "")
	  result = _PortionSpecText[i].Text;
	else
	  result = result + " " + _PortionSpecText[i].Text;
  
  for(i=0; i<spec.ListDepth; i++)
    result = (gString) "LIST(" + result + ")";    
  return result;
}


#include "gambitio.h"

PortionSpec TextToPortionSpec(const gString& text)
{
  int i;
  gString t = text;
  PortionSpec result;

  while(t.left(5) == "LIST(")
  {
    result.ListDepth++;
    t = t.mid(t.length()-6, 6);
  }
  for(i=0; i<NumPortionSpecs; i++)
    if(t.left(strlen(_PortionSpecText[i].Text)) == _PortionSpecText[i].Text)
    {
      result.Type = result.Type | _PortionSpecText[i].Type;
      t = t.right(t.length() - strlen(_PortionSpecText[i].Text));
      if(t.left(1) == " ")
	t.remove(0);
    }
  return result;
}


void PrintPortionSpec( gOutput& s, PortionSpec type )
{
  s << PortionSpecToText( type );
}

gOutput& operator << ( gOutput& s, PortionSpec spec )
{
  PrintPortionSpec( s, spec );
  return s;
}
