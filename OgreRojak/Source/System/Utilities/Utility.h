#pragma once

class System_Utility
{
	static LARGE_INTEGER	Time_Start, Time_End, Time_Frequency;
public:
	/* Debug Use */
	static void				CompilerCommandLine(std::string Text, ...);	
	// Use the Macro WritecommandLine instead of this
	// Reason : release mode easy removal

	/* Text */
	static std::wstring		ConvertToWideText(const std :: string & Text);
	static std::string		ConvertToASCIText(const std :: wstring & Text);

	static std::string		LowerCase(const std :: string & Text);
	static std::string		UpperCase(const std :: string & Text);
	
	static std::string		FormatText(std::string Format, ...);	// Does static Printing on string
	/* Values */
	static float			RandomFloat(float Min, float Max);
	static double			RandomDouble(double Min, double Max);

	/* High resolution Timer */
	static void				Start();
	static float			End();

	/* Retrieve Ogre Mesh Information */
	/* outVertices and out Indices must be empty Pointers do not pass NULL as a parameter */
	static bool				RetrieveMeshInformation(const Ogre::Mesh *	inMesh, 

													size_t &						outVertexCount,
													std::vector<float> &			outVertices,
													size_t &						outIndexCount,
													std::vector<int> &				outIndices);

	static bool				ChangeMeshIndices(	Ogre::Mesh	* inMesh,
												std::vector<int>	&	inIndices);
};

class System_HiResTimer
{
	LARGE_INTEGER	Time_Start, Time_End, Time_Frequency;
	bool			bisActive;
public:
	void	Start();
	float	End();
};