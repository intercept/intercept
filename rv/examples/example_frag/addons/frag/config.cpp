class CfgPatches {
	class Intercept_Example_Frag {
		units[] = {""};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"Intercept_Core"};
		version = 0.1;
	};
};

class CfgFunctions
{
	class Intercept
	{
		class boot
		{
			class boot_loader
			{
				preStart = 1;
                file = "z\intercept\rv\examples\examples_frag\addons\frag\boot.sqf";
                headerType = -1;
			};
		};
	};
};