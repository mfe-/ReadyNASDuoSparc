// * this is for making emacs happy: -*-Mode: C++;-*-
/****************************************************************************
 * Copyright (c) 1998-2002,2003 Free Software Foundation, Inc.              *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************
 *   Author: Juergen Pfeifer, 1997                                          *
 ****************************************************************************/

// $Id: cursslk.h,v 1.9 2003/10/25 15:04:46 tom Exp $

#ifndef NCURSES_CURSSLK_H_incl
#define NCURSES_CURSSLK_H_incl

#include <ncursesw/cursesw.h>

class NCURSES_IMPEXP Soft_Label_Key_Set {
public:
  // This inner class represents the attributes of a Soft Label Key (SLK)
  class NCURSES_IMPEXP Soft_Label_Key {
    friend class Soft_Label_Key_Set;
  public:
    typedef enum { Left=0, Center=1, Right=2 } Justification;

  private:
    char *label;           // The Text of the Label
    Justification format;  // The Justification
    int num;               // The number of the Label

    Soft_Label_Key() : label((char*)0),format(Left),num(-1) {
    }
    
    virtual ~Soft_Label_Key() {
      delete[] label;
    };

  public:
    // Set the text of the Label
    void operator=(char *text);
    
    // Set the Justification of the Label
    inline void operator=(Justification just) {
      format = just;
    }
	 
    // Retrieve the text of the label
    inline char* operator()(void) const {
      return label; 
    }
  };
  
public:
  typedef enum {
    None                = -1,
    Three_Two_Three     = 0,
    Four_Four           = 1,
    PC_Style            = 2,
    PC_Style_With_Index = 3
  } Label_Layout;

private:
  static long NCURSES_IMPEXP count;               // Number of Key Sets
  static Label_Layout NCURSES_IMPEXP  format;     // Layout of the Key Sets
  static int  NCURSES_IMPEXP num_labels;          // Number Of Labels in Key Sets
  bool NCURSES_IMPEXP b_attrInit;                 // Are attributes initialized
  
  Soft_Label_Key *slk_array;       // The array of SLK's

  // Init the Key Set
  void init();

  // Activate or Deactivate Label# i, Label counting starts with 1!
  void activate_label(int i, bool bf=TRUE);

  // Activate of Deactivate all Labels
  void activate_labels(bool bf);

protected:
  inline void Error (const char* msg) const THROWS(NCursesException) {
    THROW(new NCursesException (msg));
  }

  // Remove SLK's from screen
  void clear() { 
    if (ERR==::slk_clear())
      Error("slk_clear");
  }    

  // Restore them
  void restore() { 
    if (ERR==::slk_restore())
      Error("slk_restore");
  }

public:

  // Construct a Key Set, use the most comfortable layout as default.
  // You must create a Soft_Label_Key_Set before you create any object of
  // the NCursesWindow, NCursesPanel or derived classes. (Actually before
  // ::initscr() is called).
  Soft_Label_Key_Set(Label_Layout fmt);

  // This constructor assumes, that you already constructed a Key Set
  // with a layout by the constructor above. This layout will be reused.
  NCURSES_IMPEXP Soft_Label_Key_Set();

  virtual ~Soft_Label_Key_Set();

  // Get Label# i. Label counting starts with 1!
  NCURSES_IMPEXP Soft_Label_Key& operator[](int i);

  // Retrieve number of Labels
  inline int labels() const { return num_labels; }          

  // Refresh the SLK portion of the screen
  inline void refresh() { 
    if (ERR==::slk_refresh())
      Error("slk_refresh");
  }

  // Mark the SLK portion of the screen for refresh, defer actual refresh
  // until next update call.
  inline void noutrefresh() { 
    if (ERR==::slk_noutrefresh())
      Error("slk_noutrefresh");
  }

  // Mark the whole SLK portion of the screen as modified
  inline void touch() { 
    if (ERR==::slk_touch())
      Error("slk_touch");
  }

  // Activate Label# i
  inline void show(int i) {
    activate_label(i,FALSE);
    activate_label(i,TRUE);
  }

  // Hide Label# i
  inline void hide(int i) {
    activate_label(i,FALSE);
  }

  // Show all Labels
  inline void show() {
    activate_labels(FALSE);
    activate_labels(TRUE);
  }

  // Hide all Labels
  inline void hide() {
    activate_labels(FALSE);
  }

  inline void attron(attr_t attrs) {
    if (ERR==::slk_attron(attrs))
      Error("slk_attron");
  }

  inline void attroff(attr_t attrs) {
    if (ERR==::slk_attroff(attrs))
      Error("slk_attroff");
  }

  inline void attrset(attr_t attrs) {
    if (ERR==::slk_attrset(attrs))
      Error("slk_attrset");
  }

  inline void color(short color_pair_number) {
    if (ERR==::slk_color(color_pair_number))
      Error("slk_color");
  }

  inline attr_t attr() const {
    return ::slk_attr();
  }
};

#endif // NCURSES_CURSSLK_H_incl
