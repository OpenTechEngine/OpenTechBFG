
/*
 * FormattedListboxTextItem.h
 *
 *  Created on: Jan 9, 2015
 *      Author: kordex
 */
#if 0
#ifndef FORMATTEDLISTBOXTEXTITEM_H_
#define FORMATTEDLISTBOXTEXTITEM_H_

#include "../wrap_cegui.h"

namespace CEGUIConsole
{

//! A ListboxItem based class that can do horizontal text formating.
class FormattedListboxTextItem : public CEGUI::ListboxTextItem
{
public:
	//! Constructor
	FormattedListboxTextItem( const CEGUI::String& text,
							  const CEGUI::HorizontalTextFormatting format = CEGUI::HTF_LEFT_ALIGNED,
							  const uint item_id = 0,
							  void* const item_data = 0,
							  const bool disabled = false,
							  const bool auto_delete = true );
							  
	//! Destructor.
	~FormattedListboxTextItem();
	
	//! Return the current formatting set.
	CEGUI::HorizontalTextFormatting getFormatting() const;
	/*!
	    Set the formatting.  You should call Listbox::handleUpdatedItemData
	    after setting the formatting in order to update the listbox.  We do not
	    do it automatically since you may wish to batch changes to multiple
	    items and multiple calls to handleUpdatedItemData is wasteful.
	*/
	void setFormatting( const CEGUI::HorizontalTextFormatting fmt );
	
	// overwrote functions.
	CEGUI::Size getPixelSize( void ) const;
	void draw( CEGUI::GeometryBuffer& buffer, const CEGUI::Rect& targetRect,
			   float alpha, const CEGUI::Rect* clipper ) const;
			   
protected:
	//! Helper to create a FormattedRenderedString of an appropriate type.
	void setupStringFormatter() const;
	//! Current formatting set
	CEGUI::HorizontalTextFormatting d_formatting;
	//! Class that renders RenderedString with some formatting.
	mutable CEGUI::FormattedRenderedString* d_formattedRenderedString;
	//! Tracks target area for rendering so we can reformat when needed
	mutable CEGUI::Size d_formattingAreaSize;
};

}

#endif /* FORMATTEDLISTBOXTEXTITEM_H_ */
#endif
