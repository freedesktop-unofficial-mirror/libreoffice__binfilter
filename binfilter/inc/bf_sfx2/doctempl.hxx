/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: doctempl.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:15:09 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _SFXDOCTEMPL_HXX
#define _SFXDOCTEMPL_HXX

#ifndef _REF_HXX //autogen
#include <tools/ref.hxx>
#endif
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
namespace binfilter {

// CLASS -----------------------------------------------------------------

class SfxObjectShell;

#ifndef SFX_DECL_OBJECTSHELL_DEFINED
#define SFX_DECL_OBJECTSHELL_DEFINED
SV_DECL_REF(SfxObjectShell)
SV_DECL_LOCK(SfxObjectShell)
#endif

class SfxDocTemplate_Impl;

#ifndef SFX_DECL_DOCTEMPLATES_DEFINED
#define SFX_DECL_DOCTEMPLATES_DEFINED
SV_DECL_REF(SfxDocTemplate_Impl)
#endif

// class SfxDocumentTemplates --------------------------------------------

class SfxDocumentTemplates
{
private:
    SfxDocTemplate_ImplRef  pImp;

//STRIP001  BOOL                CopyOrMove( USHORT nTargetRegion, USHORT nTargetIdx,
//STRIP001                                  USHORT nSourceRegion, USHORT nSourceIdx, BOOL bMove );
public:
                        SfxDocumentTemplates();
                        SfxDocumentTemplates(const SfxDocumentTemplates &);
                        ~SfxDocumentTemplates();

    BOOL                IsConstructed() { return pImp != NULL; }
    void                Construct();

    static BOOL         SaveDir( /*SfxTemplateDir &rEntry */ ) ;
    const SfxDocumentTemplates &operator=(const SfxDocumentTemplates &);

//STRIP001  BOOL                Rescan( );      // Aktualisieren
//STRIP001     void                ReInitFromComponent();

    BOOL                IsRegionLoaded( USHORT nIdx ) const;
    USHORT              GetRegionCount() const;
    const String&       GetRegionName(USHORT nIdx) const;                   //dv!
    String              GetFullRegionName(USHORT nIdx) const;
    USHORT              GetRegionNo( const String &rRegionName ) const;

    USHORT              GetCount(USHORT nRegion) const;
    USHORT              GetCount( const String &rName) const;
    const String&       GetName(USHORT nRegion, USHORT nIdx) const;         //dv!
    String              GetFileName(USHORT nRegion, USHORT nIdx) const;
    String              GetPath(USHORT nRegion, USHORT nIdx) const;

    String              GetDefaultTemplatePath(const String &rLongName);

    // Pfad zur Vorlage geben lassen; logischer Name muss angegeben
    // werden, damit beim Ueberschreiben einer Vorlage der
    // richtige Dateiname gefunden werden kann
    String              GetTemplatePath(USHORT nRegion, const String &rLongName) const;

    // Speichern als Vorlage hat geklappt -> Aktualisieren
    void            NewTemplate(USHORT nRegion,
                                const String &rLongName,
                                const String &rFileName);

//STRIP001  BOOL            Copy(USHORT nTargetRegion,
//STRIP001                       USHORT nTargetIdx,
//STRIP001                       USHORT nSourceRegion,
//STRIP001                       USHORT nSourceIdx);
//STRIP001  BOOL            Move(USHORT nTargetRegion,
//STRIP001                       USHORT nTargetIdx,
//STRIP001                       USHORT nSourceRegion,
//STRIP001                       USHORT nSourceIdx);
//STRIP001  BOOL            Delete(USHORT nRegion, USHORT nIdx);
//STRIP001  BOOL            InsertDir(const String &rText, USHORT nRegion);
//STRIP001  BOOL            SetName(const String &rName, USHORT nRegion, USHORT nIdx);

//STRIP001  BOOL            CopyTo(USHORT nRegion, USHORT nIdx, const String &rName) const;
//STRIP001  BOOL            CopyFrom(USHORT nRegion, USHORT nIdx, String &rName);

//STRIP001  SfxObjectShellRef CreateObjectShell(USHORT nRegion, USHORT nIdx);
//STRIP001  BOOL            DeleteObjectShell(USHORT, USHORT);

//STRIP001  BOOL            GetFull( const String& rRegion, const String& rName, String& rPath );
    BOOL            GetLogicNames( const String& rPath, String& rRegion, String& rName ) const;

    /** updates the configuration where the document templates structure is stored.

        <p>The info about the document templates (which files, which groups etc.) is stored in the
        configuration. This means that just by copying files into OOo's template directories, this
        change is not reflected in the SfxDocumentTemplates - 'cause the configuration is not synchronous with
        the file system. This can be enforced with this method.</p>

    @param _bSmart
        The update of the configuration is rather expensive - nothing you want to do regulary if you don't really
        need it. So you have the possibility to do a smart update - it first checks if the update if necessary.
        In case the update is needed, the additional check made it somewhat more expensive. In case it's not
        necessary (which should be the usual case), the check alone is (much) less expensive than the real update.
        <br/>
        So set <arg>_bSmart</arg> to <TRUE/> to do a check for necessity first.
    */
//STRIP001  void            Update( sal_Bool _bSmart = sal_True );
};

}//end of namespace binfilter
#endif // #ifndef _SFXDOCTEMPL_HXX

