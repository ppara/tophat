/*
Copyright_License {

  Top Hat Soaring Glide Computer - http://www.tophatsoaring.org/
  Copyright (C) 2000-2016 The Top Hat Soaring Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#ifndef XCSOAR_FORM_EDIT_HPP
#define XCSOAR_FORM_EDIT_HPP

#include "Form/Control.hpp"
#include "Screen/Point.hpp"
#include "Util/tstring.hpp"

struct DialogLook;
class DataField;
class ContainerWindow;

/**
 * The WndProperty class implements a WindowControl with a caption label and
 * an editable field (the Editor).
 */
class WndProperty : public WindowControl {
  typedef bool (*EditCallback)(const TCHAR *caption, DataField &df,
                               const TCHAR *help_text);

  const DialogLook &look;

  /** Position of the Editor Control */
  PixelRect edit_rc;

  /** Width reserved for the caption of the Control */
  int caption_width;

  tstring value;

  DataField *data_field;

  EditCallback edit_callback;

  bool read_only;

  bool dragging, pressed;

  /** optional caption used while editing */
  StaticString<254> editing_caption;

  /** paints highlight for the text and background */
  bool highlighted;

public:
  /**
   * Constructor of the WndProperty
   * @param Parent The parent ContainerControl
   * @param Caption Caption of the Control
   * @param CaptionWidth Width of the Caption of the Control
   */
  WndProperty(ContainerWindow &parent, const DialogLook &look,
              const TCHAR *Caption,
              const PixelRect &rc, int CaptionWidth,
              const WindowStyle style);

  WndProperty(const DialogLook &_look);

  /** Destructor */
  ~WndProperty();

  void Create(ContainerWindow &parent, const PixelRect &rc,
              const TCHAR *_caption,
              unsigned _caption_width,
              const WindowStyle style);

public:
  /**
   * Returns the recommended caption width, measured by the dialog
   * font.
   */
  gcc_pure
  unsigned GetRecommendedCaptionWidth() const;

  void SetCaptionWidth(int caption_width);

  void RefreshDisplay();

  void SetReadOnly(bool _read_only=true) {
    read_only = _read_only;
  }

  gcc_pure
  bool IsReadOnly() const {
    return read_only;
  }

  /**
   * sets the optional caption that is used for editing
   */
  void SetEditingCaption(const TCHAR *_editing_caption) {
    editing_caption = _editing_caption;
  }

  /**
   * returns the optional caption used only while editing,
   * or if that is empty, returns the regular caption
   */
  gcc_pure
  const TCHAR * GetEditingCaption() const;

  /**
   * Starts  interactively  editing  the  value.   If  a  ComboBox  is
   * available, then the ComboPicker  will be launched, otherwise, the
   * focus and cursor is set to the control.
   *
   * @return true if the value has been modified
   */
  bool BeginEditing();

protected:
  void OnResize(PixelSize new_size) override;
  void OnSetFocus() override;
  void OnKillFocus() override;

  bool OnMouseDown(PixelScalar x, PixelScalar y) override;
  bool OnMouseUp(PixelScalar x, PixelScalar y) override;
  bool OnMouseMove(PixelScalar x, PixelScalar y, unsigned keys) override;

  bool OnKeyCheck(unsigned key_code) const override;
  bool OnKeyDown(unsigned key_code) override;

  void OnCancelMode() override;

public:
  /**
   * Returns the Control's DataField
   * @return The Control's DataField
   */
  DataField *GetDataField() {
    return data_field;
  }

  /**
   * Returns the Control's DataField
   * @return The Control's DataField
   */
  const DataField *GetDataField() const {
    return data_field;
  }

  void SetDataField(DataField *Value);

  void SetEditCallback(EditCallback _ec) {
    edit_callback = _ec;
  }

  /**
   * Sets the Editors text to the given Value
   * @param Value The new text of the Editor Control
   */
  void SetText(const TCHAR *_value);

  /**
   * sets or clears the pressed and focused attributes
   * simulating a highlight affect
   */
  void SetHighlight(bool value);

private:
  /**
   * The OnPaint event is called when the button needs to be drawn
   * (derived from PaintWindow)
   */
  void OnPaint(Canvas &canvas) override;

  /** Increases the Editor value */
  int IncValue();
  /** Decreases the Editor value */
  int DecValue();

  void UpdateLayout();
};

#endif
