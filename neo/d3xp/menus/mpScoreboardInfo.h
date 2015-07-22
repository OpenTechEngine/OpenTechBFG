/*
 * mpScoreboardInfo.h
 *
 *  Created on: 28.3.2015
 */

#ifndef MPSCOREBOARDINFO_H_
#define MPSCOREBOARDINFO_H_

namespace BFG
{

class mpScoreboardInfo
{
public:

	mpScoreboardInfo() :
		voiceState( VOICECHAT_DISPLAY_NONE ),
		score( 0 ),
		wins( 0 ),
		ping( 0 ),
		team( -1 ),
		playerNum( 0 )
	{
	}
	
	mpScoreboardInfo( const mpScoreboardInfo& src )
	{
		voiceState = src.voiceState;
		score = src.score;
		wins = src.wins;
		ping = src.ping;
		spectateData = src.spectateData;
		name = src.name;
		team = src.team;
		playerNum = src.playerNum;
	}
	
	void operator=( const mpScoreboardInfo& src )
	{
		voiceState = src.voiceState;
		score = src.score;
		wins = src.wins;
		ping = src.ping;
		spectateData = src.spectateData;
		name = src.name;
		team = src.team;
		playerNum = src.playerNum;
	}
	
	bool operator!=( const mpScoreboardInfo& otherInfo ) const
	{
	
		if( otherInfo.score != score || otherInfo.wins != wins || otherInfo.ping != ping ||
				otherInfo.spectateData != spectateData || otherInfo.name != name || otherInfo.team != team ||
				otherInfo.playerNum != playerNum || otherInfo.voiceState != voiceState )
		{
			return true;
		}
		
		return false;
	}
	
	bool operator==( const mpScoreboardInfo& otherInfo ) const
	{
	
		if( otherInfo.score != score || otherInfo.wins != wins || otherInfo.ping != ping ||
				otherInfo.spectateData != spectateData || otherInfo.name != name || otherInfo.team != team ||
				otherInfo.playerNum != playerNum || otherInfo.voiceState != voiceState )
		{
			return false;
		}
		
		return true;
	}
	
	voiceStateDisplay_t voiceState;
	int score;
	int wins;
	int ping;
	int team;
	int playerNum;
	idStr spectateData;
	idStr name;
	
};

} // namespace BFG

#endif /* MPSCOREBOARDINFO_H_ */
