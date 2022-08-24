#pragma once
#include "../styles/FontStyle.h"

namespace NSDocxRenderer
{
    class CStyleManager
    {
        public:
            bool m_bBrushWasChanged {false};
            bool m_bFontWasChanged {false};

            NSStructures::CPen				m_oPen;
            NSStructures::CBrush			m_oBrush;
            NSStructures::CFont				m_oFont;
            NSStructures::CShadow			m_oShadow;
            NSStructures::CEdgeText			m_oEdge;

            std::shared_ptr<CFontStyle> m_pCurrentStyle;

            std::vector<std::shared_ptr<CFontStyle>> m_arStyles;

            CFontManager		m_oFontManager;
            CFontManagerLight	m_oFontManagerLight;
        public:
            CStyleManager(NSFonts::IApplicationFonts *pFonts);
            virtual ~CStyleManager();

            void Clear();

            void Init(Aggplus::CMatrix *pMatrix);

            std::shared_ptr<CFontStyle> GetStyle(std::shared_ptr<CFontStyle> pTempStyle);
            std::shared_ptr<CFontStyle> GetCurrentStyle();
    };
}

