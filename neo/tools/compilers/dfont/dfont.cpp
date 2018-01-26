/*
 * dfont.cpp
 *
 *  Created on: 26 de gen. 2018
 *      Author: biel
 */

#include "../tools/compilers/dfont/dfont.h"

#include "../tools/compilers/compiler_public.h"

namespace BFG
{

/*
============
Dfont
============
*/
void Dfont( const idCmdArgs& args )
{
	int			i;
	int			start, end;
	char		path[1024];
	idStr		passedName;
	bool		leaked = false;
	bool		noCM = false;
	bool		noAAS = false;

	ResetDmapGlobals();

	if( args.Argc() < 2 )
	{
		DmapHelp();
		return;
	}

	common->Printf( "---- dmap ----\n" );

	dmapGlobals.fullCarve = true;
	dmapGlobals.shadowOptLevel = SO_MERGE_SURFACES;		// create shadows by merging all surfaces, but no super optimization
//	dmapGlobals.shadowOptLevel = SO_CLIP_OCCLUDERS;		// remove occluders that are completely covered
//	dmapGlobals.shadowOptLevel = SO_SIL_OPTIMIZE;
//	dmapGlobals.shadowOptLevel = SO_CULL_OCCLUDED;

	dmapGlobals.noLightCarve = true;

	for( i = 1 ; i < args.Argc() ; i++ )
	{
		const char* s;

		s = args.Argv( i );
		if( s[0] == '-' )
		{
			s++;
			if( s[0] == '\0' )
			{
				continue;
			}
		}

		if( !idStr::Icmp( s, "glview" ) )
		{
			dmapGlobals.glview = true;
		}
		else if( !idStr::Icmp( s, "v" ) )
		{
			common->Printf( "verbose = true\n" );
			dmapGlobals.verbose = true;
		}
		else if( !idStr::Icmp( s, "draw" ) )
		{
			common->Printf( "drawflag = true\n" );
			dmapGlobals.drawflag = true;
		}
		else if( !idStr::Icmp( s, "noFlood" ) )
		{
			common->Printf( "noFlood = true\n" );
			dmapGlobals.noFlood = true;
		}
		else if( !idStr::Icmp( s, "noLightCarve" ) )
		{
			common->Printf( "noLightCarve = true\n" );
			dmapGlobals.noLightCarve = true;
		}
		else if( !idStr::Icmp( s, "lightCarve" ) )
		{
			common->Printf( "noLightCarve = false\n" );
			dmapGlobals.noLightCarve = false;
		}
		else if( !idStr::Icmp( s, "noOpt" ) )
		{
			common->Printf( "noOptimize = true\n" );
			dmapGlobals.noOptimize = true;
		}
		else if( !idStr::Icmp( s, "verboseentities" ) )
		{
			common->Printf( "verboseentities = true\n" );
			dmapGlobals.verboseentities = true;
		}
		else if( !idStr::Icmp( s, "noCurves" ) )
		{
			common->Printf( "noCurves = true\n" );
			dmapGlobals.noCurves = true;
		}
		else if( !idStr::Icmp( s, "noModels" ) )
		{
			common->Printf( "noModels = true\n" );
			dmapGlobals.noModelBrushes = true;
		}
		else if( !idStr::Icmp( s, "noClipSides" ) )
		{
			common->Printf( "noClipSides = true\n" );
			dmapGlobals.noClipSides = true;
		}
		else if( !idStr::Icmp( s, "noCarve" ) )
		{
			common->Printf( "noCarve = true\n" );
			dmapGlobals.fullCarve = false;
		}
		else if( !idStr::Icmp( s, "shadowOpt" ) )
		{
			dmapGlobals.shadowOptLevel = ( shadowOptLevel_t )atoi( args.Argv( i + 1 ) );
			common->Printf( "shadowOpt = %i\n", dmapGlobals.shadowOptLevel );
			i += 1;
		}
		else if( !idStr::Icmp( s, "noTjunc" ) )
		{
			// triangle optimization won't work properly without tjunction fixing
			common->Printf( "noTJunc = true\n" );
			dmapGlobals.noTJunc = true;
			dmapGlobals.noOptimize = true;
			common->Printf( "forcing noOptimize = true\n" );
		}
		else if( !idStr::Icmp( s, "noCM" ) )
		{
			noCM = true;
			common->Printf( "noCM = true\n" );
		}
		else if( !idStr::Icmp( s, "noAAS" ) )
		{
			noAAS = true;
			common->Printf( "noAAS = true\n" );
		}
		else
		{
			break;
		}
	}

	if( i >= args.Argc() )
	{
		common->Error( "usage: dmap [options] mapfile" );
	}

	passedName = args.Argv( i );		// may have an extension
	passedName.BackSlashesToSlashes();
	if( passedName.Icmpn( "maps/", 4 ) != 0 )
	{
		passedName = "maps/" + passedName;
	}

	idStr stripped = passedName;
	stripped.StripFileExtension();
	idStr::Copynz( dmapGlobals.mapFileBase, stripped, sizeof( dmapGlobals.mapFileBase ) );

	bool region = false;
	// if this isn't a regioned map, delete the last saved region map
	if( passedName.Right( 4 ) != ".reg" )
	{
		idStr::snPrintf( path, sizeof( path ), "%s.reg", dmapGlobals.mapFileBase );
		fileSystem->RemoveFile( path );
	}
	else
	{
		region = true;
	}


	passedName = stripped;

	// delete any old line leak files
	idStr::snPrintf( path, sizeof( path ), "%s.lin", dmapGlobals.mapFileBase );
	fileSystem->RemoveFile( path );

	// delete any old generated binary proc files
	idStr generated = va( "generated/%s.bproc", dmapGlobals.mapFileBase );
	fileSystem->RemoveFile( generated.c_str() );

	//
	// start from scratch
	//
	start = Sys_Milliseconds();

	if( !LoadDMapFile( passedName ) )
	{
		return;
	}

	if( ProcessModels() )
	{
		WriteOutputFile();
	}
	else
	{
		leaked = true;
	}

	FreeDMapFile();

	common->Printf( "%i total shadow triangles\n", dmapGlobals.totalShadowTriangles );
	common->Printf( "%i total shadow verts\n", dmapGlobals.totalShadowVerts );

	end = Sys_Milliseconds();
	common->Printf( "-----------------------\n" );
	common->Printf( "%5.0f seconds for dmap\n", ( end - start ) * 0.001f );

	if( !leaked )
	{

		if( !noCM )
		{

			// make sure the collision model manager is not used by the game
			cmdSystem->BufferCommandText( CMD_EXEC_NOW, "disconnect" );

			// create the collision map
			start = Sys_Milliseconds();

			collisionModelManager->LoadMap( dmapGlobals.dmapFile );
			collisionModelManager->FreeMap();

			end = Sys_Milliseconds();
			common->Printf( "-------------------------------------\n" );
			common->Printf( "%5.0f seconds to create collision map\n", ( end - start ) * 0.001f );
		}

		if( !noAAS && !region )
		{
			// create AAS files
			RunAAS_f( args );
		}
	}

	// free the common .map representation
	delete dmapGlobals.dmapFile;

	// clear the map plane list
	dmapGlobals.mapPlanes.Clear();
}

/*
============
Dfont_f
============
*/
void Dfont_f( const idCmdArgs& args )
{

	common->ClearWarnings( "running dmap" );

	// refresh the screen each time we print so it doesn't look
	// like it is hung
	common->SetRefreshOnPrint( true );
	Dfont( args );
	common->SetRefreshOnPrint( false );

	common->PrintWarnings();
}

} // namespace BFG
