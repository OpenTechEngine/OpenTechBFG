/*
 * FormattedListboxTextItem.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: kordex
 */

// see http://cegui.org.uk/forum/viewtopic.php?f=10&t=4322

#if 0
#include "FormattedListboxTextItem.h"

namespace CEGUIConsole
{

//----------------------------------------------------------------------------//
FormattedListboxTextItem::FormattedListboxTextItem( const CEGUI::String& text,
		const CEGUI::HorizontalTextFormatting format,
		const uint item_id,
		void* const item_data,
		const bool disabled,
		const bool auto_delete ) :
	// initialise base class
	ListboxTextItem( text, item_id, item_data, disabled, auto_delete ),
	// initialise subclass fields
	d_formatting( format ),
	d_formattedRenderedString( 0 ),
	d_formattingAreaSize( 0, 0 )
{
}

//----------------------------------------------------------------------------//
FormattedListboxTextItem::~FormattedListboxTextItem()
{
	delete d_formattedRenderedString;
}

//----------------------------------------------------------------------------//
CEGUI::HorizontalTextFormatting FormattedListboxTextItem::getFormatting() const
{
	return d_formatting;
}

//----------------------------------------------------------------------------//
void FormattedListboxTextItem::setFormatting( const CEGUI::HorizontalTextFormatting fmt )
{
	if( fmt == d_formatting )
		return;
		
	d_formatting = fmt;
	delete d_formattedRenderedString;
	d_formattedRenderedString = 0;
	d_formattingAreaSize = CEGUI::Size( 0, 0 );
}

//----------------------------------------------------------------------------//
CEGUI::Size FormattedListboxTextItem::getPixelSize( void ) const
{
	if( !d_owner )
		return CEGUI::Size( 0, 0 );
		
	// reparse text if we need to.
	if( !d_renderedStringValid )
		parseTextString();
		
	// create formatter if needed
	if( !d_formattedRenderedString )
		setupStringFormatter();
		
	// get size of render area from target window, to see if we need to reformat
	const CEGUI::Size area_sz( static_cast<const CEGUI::Listbox*>( d_owner )->
							   getListRenderArea().getSize() );
	if( area_sz != d_formattingAreaSize )
	{
		d_formattedRenderedString->format( d_owner, area_sz );
		d_formattingAreaSize = area_sz;
	}
	
	return Size( d_formattedRenderedString->getHorizontalExtent( d_owner ),
				 d_formattedRenderedString->getVerticalExtent( d_owner ) );
}

//----------------------------------------------------------------------------//
void FormattedListboxTextItem::draw( CEGUI::GeometryBuffer& buffer,
									 const CEGUI::Rect& targetRect,
									 float alpha, const CEGUI::Rect* clipper ) const
{
	// reparse text if we need to.
	if( !d_renderedStringValid )
		parseTextString();
		
	// create formatter if needed
	if( !d_formattedRenderedString )
		setupStringFormatter();
		
	// get size of render area from target window, to see if we need to reformat
	// NB: We do not use targetRect, since it may not represent the same area.
	const CEGUI::Size area_sz( static_cast<const CEGUI::Listbox*>( d_owner )->
							   getListRenderArea().getSize() );
	if( area_sz != d_formattingAreaSize )
	{
		d_formattedRenderedString->format( Window, area_sz );
		d_formattingAreaSize = area_sz;
	}
	
	// draw selection imagery
	if( d_selected && d_selectBrush != 0 )
		d_selectBrush->draw( buffer, targetRect, clipper,
							 getModulateAlphaColourRect( d_selectCols, alpha ) );
							 
	// factor the window alpha into our colours.
	const CEGUI::ColourRect final_colours(
		getModulateAlphaColourRect( CEGUI::ColourRect( 0xFFFFFFFF ), alpha ) );
		
	// draw the formatted text
	d_formattedRenderedString->draw( d_owner, buffer, targetRect.getPosition(),
									 &final_colours, clipper );
}

//----------------------------------------------------------------------------//
void FormattedListboxTextItem::setupStringFormatter() const
{
	// delete any existing formatter
	delete d_formattedRenderedString;
	d_formattedRenderedString = 0;
	
	// create new formatter of whichever type...
	switch( d_formatting )
	{
		case CEGUI::HTF_LEFT_ALIGNED:
			d_formattedRenderedString =
				new CEGUI::LeftAlignedRenderedString( d_renderedString );
			break;
			
		case CEGUI::HTF_RIGHT_ALIGNED:
			d_formattedRenderedString =
				new CEGUI::RightAlignedRenderedString( d_renderedString );
			break;
			
		case CEGUI::HTF_CENTRE_ALIGNED:
			d_formattedRenderedString =
				new CEGUI::CentredRenderedString( d_renderedString );
			break;
			
		case CEGUI::HTF_JUSTIFIED:
			d_formattedRenderedString =
				new CEGUI::JustifiedRenderedString( d_renderedString );
			break;
			
		case CEGUI::HTF_WORDWRAP_LEFT_ALIGNED:
			d_formattedRenderedString =
				new CEGUI::RenderedStringWordWrapper
			<CEGUI::LeftAlignedRenderedString>( d_renderedString );
			break;
			
		case CEGUI::HTF_WORDWRAP_RIGHT_ALIGNED:
			d_formattedRenderedString =
				new CEGUI::RenderedStringWordWrapper
			<CEGUI::RightAlignedRenderedString>( d_renderedString );
			break;
			
		case CEGUI::HTF_WORDWRAP_CENTRE_ALIGNED:
			d_formattedRenderedString =
				new CEGUI::RenderedStringWordWrapper
			<CEGUI::CentredRenderedString>( d_renderedString );
			break;
			
		case CEGUI::HTF_WORDWRAP_JUSTIFIED:
			d_formattedRenderedString =
				new CEGUI::RenderedStringWordWrapper
			<CEGUI::JustifiedRenderedString>( d_renderedString );
			break;
	}
}

//----------------------------------------------------------------------------//
}
#endif
