/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file       zypp/repo/RepoInfoBase.cc
 *
 */
#include <iostream>

#include "zypp/repo/RepoInfoBase.h"
#include "zypp/repo/RepoInfoBaseImpl.h"

using namespace std;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace repo
  { /////////////////////////////////////////////////////////////////


  /** \relates RepoInfo::Impl Stream output */
  inline std::ostream & operator<<( std::ostream & str, const RepoInfoBase::Impl & obj )
  {
    return str << "RepoInfo::Impl";
  }

  ///////////////////////////////////////////////////////////////////
  //
  //    CLASS NAME : RepoInfoBase
  //
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  //
  //    METHOD NAME : RepoInfo::RepoInfo
  //    METHOD TYPE : Ctor
  //
  RepoInfoBase::RepoInfoBase()
  : _pimpl( new Impl() )
  {}

  ///////////////////////////////////////////////////////////////////
  //
  //    METHOD NAME : RepoInfoBase::~RepoInfoBase
  //    METHOD TYPE : Dtor
  //
  RepoInfoBase::~RepoInfoBase()
  {}

  RepoInfoBase & RepoInfoBase::setEnabled( bool enabled )
  {
    _pimpl->enabled = enabled;
    return *this;
  }

  RepoInfoBase & RepoInfoBase::setAutorefresh( bool autorefresh )
  {
    _pimpl->autorefresh = autorefresh;
    return *this;
  }

  RepoInfoBase & RepoInfoBase::setAlias( const std::string &alias )
  {
    _pimpl->alias = alias;
    // replace slashes with underscores
    std::string fnd="/";
    std::string rep="_";
    std::string escaped_alias = alias;
    size_t pos = escaped_alias.find(fnd);
    while(pos!=string::npos)
    {
      escaped_alias.replace(pos,fnd.length(),rep);
      pos = escaped_alias.find(fnd,pos+rep.length());
    }
    _pimpl->escaped_alias = escaped_alias;
    return *this;
  }

  RepoInfoBase & RepoInfoBase::setName( const std::string &name )
  {
    _pimpl->name = name;
    return *this;
  }

  RepoInfoBase & RepoInfoBase::setFilepath( const Pathname &filepath )
  {
    _pimpl->filepath = filepath;
    return *this;
  }

  // true by default (if not set by setEnabled())
  bool RepoInfoBase::enabled() const
  { return indeterminate(_pimpl->enabled) ? true : (bool) _pimpl->enabled; }

  // false by default (if not set by setAutorefresh())
  bool RepoInfoBase::autorefresh() const
  { return indeterminate(_pimpl->autorefresh) ? false : (bool) _pimpl->autorefresh; }

  std::string RepoInfoBase::alias() const
  { return _pimpl->alias; }

  std::string RepoInfoBase::escaped_alias() const
  { return _pimpl->escaped_alias; }

  std::string RepoInfoBase::name() const
  {
    if ( _pimpl->name.empty() )
    {
      return alias();
    }

    //! \todo repo::RepoVariablesStringReplacer replacer;
    return _pimpl->name; //replacer(_pimpl->name);
  }

  Pathname RepoInfoBase::filepath() const
  { return _pimpl->filepath; }


  std::ostream & RepoInfoBase::dumpOn( std::ostream & str ) const
  {
    str << "--------------------------------------" << std::endl;
    str << "- alias       : " << alias() << std::endl;
    str << "- alias       : " << name() << std::endl;
    str << "- enabled     : " << enabled() << std::endl;
    str << "- autorefresh : " << autorefresh() << std::endl;

    return str;
  }

  std::ostream & RepoInfoBase::dumpAsIniOn( std::ostream & str ) const
  {
    // we save the original data without variable replacement
    str << "[" << alias() << "]" << endl;
    str << "name=" << name() << endl;
    str << "enabled=" << (enabled() ? "1" : "0") << endl;
    str << "autorefresh=" << (autorefresh() ? "1" : "0") << endl;

    return str;
  }

  std::ostream & operator<<( std::ostream & str, const RepoInfoBase & obj )
  {
    return obj.dumpOn(str);
  }

    /////////////////////////////////////////////////////////////////
  } // namespace repo
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
