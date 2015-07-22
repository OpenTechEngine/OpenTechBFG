fx fx/effect
{
	{
		delay 0
		name "particle2"
		duration 8
		restart 0
		model "sparks.prt"
	}
	{
		delay 0
		sound "electrical_sparks"
		duration 2.5

	}
	{	// fade out the blast light
		delay 4
		name "part2"
		duration 4
		usemodel "particle2"
		fadeOut 4
	}
}