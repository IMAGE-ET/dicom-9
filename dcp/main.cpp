// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "precomp.h"

using namespace Application::Infrastructure;

static const struct
{
    const wchar_t* Name;
    unsigned NArgs;
    bool IsRequired;
} DCPArguments[] =
{
    { L"--dataPath",   1, true  },
    { L"--mean",       0, false },
    { L"--stddev",     0, false },
    { L"--voxel-size", 3, false }
};

class DCPApplication : public ApplicationBase<DCPApplication>
{
    HRESULT EnsureOption(const wchar_t* pOptionName)
    {
        bool isSet;
        RETURN_IF_FAILED(IsOptionSet(pOptionName, &isSet));
        if (!isSet)
        {
            RETURN_IF_FAILED(PrintInvalidArgument(true, pOptionName, L"Option not set."));
            return E_FAIL;
        }

        return S_OK;
    }
public:
    HRESULT Run()
    {
        RETURN_IF_FAILED(EnsureOption(L"--voxel-size"));

        unsigned z;
        RETURN_IF_FAILED(GetOptionParameterAt<2>(L"--voxel-size", &z));

        RETURN_IF_FAILED(EnsureOption(L"--mean"));
        return S_OK;
    }

    HRESULT GetLengthOfArgumentsToFollow(wchar_t* pwzArgName, unsigned* nArgsToFollow)
    {
        RETURN_HR_IF_NULL(E_POINTER, nArgsToFollow);
        RETURN_HR_IF_NULL(E_POINTER, pwzArgName);

        *nArgsToFollow = 0;

        auto foundIt = 
            std::find_if(
                std::begin(DCPArguments),
                std::end(DCPArguments),
                [pwzArgName](const auto& argument)
                {
                    return _wcsicmp(argument.Name, pwzArgName) == 0;
                }
            );

        RETURN_HR_IF(E_INVALIDARG, foundIt == std::end(DCPArguments));

        // Set the number of return args to follow
        *nArgsToFollow = foundIt->NArgs;

        return S_OK;
    };

    HRESULT ValidateArgument(const wchar_t* pArgumentName, bool* isValid)
    {
        RETURN_HR_IF_NULL(E_INVALIDARG, pArgumentName);
        RETURN_HR_IF_NULL(E_POINTER, isValid);
        *isValid = true;

        if (_wcsicmp(pArgumentName, L"--voxel-size") == 0)
        {
            unsigned tmp;
            *isValid = SUCCEEDED(GetOptionParameterAt<0>(L"--voxel-size", &tmp));
            RETURN_HR_IF_FALSE(S_OK, *isValid);
            *isValid = SUCCEEDED(GetOptionParameterAt<1>(L"--voxel-size", &tmp));
            RETURN_HR_IF_FALSE(S_OK, *isValid);
            *isValid = SUCCEEDED(GetOptionParameterAt<2>(L"--voxel-size", &tmp));
            RETURN_HR_IF_FALSE(S_OK, *isValid);
        }
        return S_OK;
    }

    HRESULT PrintHelp()
    {
        static const auto HELP = LR"(
DCPApplication Reference (dcaapplication.exe)

Parameter               Usage
--------------------------------------------------------------------------------------------------------
--dataPath              The path (absolute: c:\..., or relative) to a folder containing dicoms images.

                        Examples:
                        dcaapplication.exe --dataPath "C:\foldername" [[OTHER PARAMETERS]]
                        dcaapplication.exe --dataPath "C:\foldername\subfolder\" [[OTHER PARAMETERS]]
                        dcaapplication.exe --dataPath "folder" [[OTHER PARAMETERS]]
                        dcaapplication.exe --dataPath "folder\subdolder\" [[OTHER PARAMETERS]]

--mean                  Compute the voxel means

                        Examples:
                        dcaapplication.exe --mean [[OTHER PARAMETERS]]

--stddev                Compute the voxel standard deviations

                        Examples:
                        dcaapplication.exe --stddev [[OTHER PARAMETERS]]

--voxel-size            The dimensions of each voxel in the form: "dim_one_size dim_two_size dim_three_size"
                        in millimeters.

                        Example: Setting 2cm cubed voxel size
                        dcaapplication.exe --voxel-shape 20 20 20 [[OTHER PARAMETERS]]
)";
        wprintf(HELP);
        return S_OK;
    }
};


int main()
{
    DCPApplication::Execute();
    return 0;
}

