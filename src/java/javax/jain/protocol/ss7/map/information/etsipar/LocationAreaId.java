/*
 @(#) $RCSfile: LocationAreaId.java,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 11:34:40 $ <p>
 
 Copyright &copy; 2008-2009  Monavacon Limited <a href="http://www.monavacon.com/">&lt;http://www.monavacon.com/&gt;</a>. <br>
 Copyright &copy; 2001-2008  OpenSS7 Corporation <a href="http://www.openss7.com/">&lt;http://www.openss7.com/&gt;</a>. <br>
 Copyright &copy; 1997-2001  Brian F. G. Bidulock <a href="mailto:bidulock@openss7.org">&lt;bidulock@openss7.org&gt;</a>. <p>
 
 All Rights Reserved. <p>
 
 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation, version 3 of the license. <p>
 
 This program is distributed in the hope that it will be useful, but <b>WITHOUT
 ANY WARRANTY</b>; without even the implied warranty of <b>MERCHANTABILITY</b>
 or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.  See the GNU Affero General Public
 License for more details. <p>
 
 You should have received a copy of the GNU Affero General Public License along
 with this program.  If not, see
 <a href="http://www.gnu.org/licenses/">&lt;http://www.gnu.org/licenses/&gt</a>,
 or write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA. <p>
 
 <em>U.S. GOVERNMENT RESTRICTED RIGHTS</em>.  If you are licensing this
 Software on behalf of the U.S. Government ("Government"), the following
 provisions apply to you.  If the Software is supplied by the Department of
 Defense ("DoD"), it is classified as "Commercial Computer Software" under
 paragraph 252.227-7014 of the DoD Supplement to the Federal Acquisition
 Regulations ("DFARS") (or any successor regulations) and the Government is
 acquiring only the license rights granted herein (the license rights
 customarily provided to non-Government users).  If the Software is supplied to
 any unit or agency of the Government other than DoD, it is classified as
 "Restricted Computer Software" and the Government's rights in the Software are
 defined in paragraph 52.227-19 of the Federal Acquisition Regulations ("FAR")
 (or any successor regulations) or, in the cases of NASA, in paragraph
 18.52.227-86 of the NASA Supplement to the FAR (or any successor regulations). <p>
 
 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See
 <a href="http://www.openss7.com/">http://www.openss7.com/</a> <p>
 
 Last Modified $Date: 2009-06-21 11:34:40 $ by $Author: brian $
 */

package javax.jain.protocol.ss7.map.information.etsipar;

import javax.jain.protocol.ss7.map.information.*;
import javax.jain.protocol.ss7.map.*;
import javax.jain.protocol.ss7.*;
import javax.jain.*;

/** This parameter class represents a Location Area Id (LAI) value as defined in the specification 3G TS 23.003. <p>
  *
  * The following rules applies for the setting of parameter components:- <ul>
  * <li>Mandatory component with no default value must be provided to the constructor.
  * <li>Mandatory component with default value need not be set.
  * <li>Optional / conditional component is by default not present. Such a component
  * becomes present by setting it. </ul> <p>
  *
  * <h4>Parameter components:-</h4> <ul>
  *
  * <li>mcc - Mobile Country Code, mandatory component with no default
  * <li>mnc - Mobile Network Code, mandatory component with no default
  * <li>lac - Location Area Code, mandatory component with no default </ul>
  *
  * @author Monavacon Limited
  * @version 1.2.2
  */
public class LocationAreaId extends MapParameter {
    /** The constructor.
      * @param mcc  Mobile Country Code (3 digits)
      * @param mnc  Mobile Network Code (2-3 digits)
      * @param lac  Location Area Code (2 bytes)
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public LocationAreaId(java.lang.String mcc, java.lang.String mnc, byte[] lac)
        throws SS7InvalidParamException {
        setMobileCountryCode(mcc);
        setMobileNetworkCode(mnc);
        setLocationAreaCode(lac);
    }
    /** Empty constructor; needed for serializable objects and beans.
      */
    public LocationAreaId()
        throws SS7InvalidParamException {
    }
    /** Change the value of the Mobile Country Code (MCC).
      * @param mcc - java.lang.String with 3 digit MCC.
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public void setMobileCountryCode(java.lang.String mcc)
        throws SS7InvalidParamException {
        if (mcc.length() == 3) {
            m_mcc = mcc;
            return;
        }
        throw new SS7InvalidParamException("Mobile Country Code length " + mcc.length() + " invalid.");
    }
    /** Get the value of the Mobile Country Code (MCC).
      * @return java.lang.String with 3 digit MCC.
      */
    public java.lang.String getMobileCountryCode() {
        return m_mcc;
    }
    /** Change the value of the Mobile Network Code (MNC).
      * @param mnc  java.lang.String with 2-3 digit MNC.
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public void setMobileNetworkCode(java.lang.String mnc)
        throws SS7InvalidParamException {
        if (2 <= mnc.length() && mnc.length() <= 3) {
            m_mnc = mnc;
            return;
        }
        throw new SS7InvalidParamException("Mobile Network Code length " + mnc.length() + " is invalid.");
    }
    /** Get the value of the Mobile Network Code (MNC).
      * @return java.lang.String with 2-3 digit MNC.
      */
    public java.lang.String getMobileNetworkCode() {
        return m_mnc;
    }
    /** Change the value of the Location Area Code (LAC).
      * @param lac  Byte array with 2 byte LAC.
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public void setLocationAreaCode(byte[] lac)
        throws SS7InvalidParamException {
        if (lac.length == 2) {
            m_lac = lac;
            return;
        }
        throw new SS7InvalidParamException("Location Area Code length "  + lac.length + " is invalid.");
    }
    /** Get the value of the Location Area Code (LAC).
      * @return Byte array with 2 byte LAC.
      */
    public byte[] getLocationAreaCode() {
        return m_lac;
    }
    /** Get the whole Location Area Id (MCC+MNC+LAC) as a java.lang.String.
      * @return java.lang.String containing LAI.
      */
    public java.lang.String toString() {
        StringBuffer b = new StringBuffer(512);
        b.append(super.toString());
        b.append("\njavax.jain.protocol.ss7.map.information.etsipar.LocationAreaId");
        b.append("\n\tm_mcc: " + m_mcc);
        b.append("\n\tm_mnc: " + m_mnc);
        b.append("\n\tm_lac: " + m_lac);
        return b.toString();
    }
    /** Compares this Location Area Id with another LAI.
      * @param lai  Location Area Id (LAI) to be compared with this LAI.
      * @return True if equal, otherwise false.
      */
    public boolean equals(java.lang.Object lai) {
        if (lai instanceof LocationAreaId) {
            LocationAreaId other = (LocationAreaId) lai;
            if (other.m_mcc == m_mcc && other.m_mnc == m_mnc && other.m_lac == m_lac)
                return true;
        }
        return false;
    }
    protected java.lang.String m_mcc = "";
    protected java.lang.String m_mnc = "";
    protected byte[] m_lac;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-