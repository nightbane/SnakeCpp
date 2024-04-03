#pragma once

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> static std::wstring ToString<point>(const point& p) {
				std::wstring w = L"(" + std::to_wstring(p.x) + L"," + std::to_wstring(p.y) + L")";
				return w;
			}
		}
	}
}
