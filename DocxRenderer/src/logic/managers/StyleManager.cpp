#include "StyleManager.h"
#include <utility>

namespace NSDocxRenderer
{
    CStyleManager::CStyleManager(NSFonts::IApplicationFonts* pFonts) :
        m_oFontManager(pFonts), m_oFontManagerLight(pFonts)
    {

    }

    CStyleManager::~CStyleManager()
    {
        Clear();
    }

    void CStyleManager::Clear()
    {
        m_arStyles.clear();
        m_pCurrentStyle.reset();
    }

    void CStyleManager::Init(Aggplus::CMatrix *pMatrix)
    {
        Clear();
        m_oFontManager.Init();

        m_oPen.SetDefaultParams();
        m_oBrush.SetDefaultParams();
        m_oFont.SetDefaultParams();
        m_oShadow.SetDefaultParams();
        m_oEdge.SetDefaultParams();

        m_oFontManager.m_pFont			= &m_oFont;
        m_oFontManager.m_pTransform		= pMatrix;
    }

    std::shared_ptr<CFontStyle> CStyleManager::GetStyle(std::shared_ptr<CFontStyle> pTempStyle)
    {
        for (const auto &pStyle : m_arStyles)
        {
            if (pStyle->IsEqual(pTempStyle))
            {
                m_pCurrentStyle = pStyle;
                return m_pCurrentStyle;
            }
        }

        pTempStyle->GenerateFontStyleId();
        m_arStyles.push_back(pTempStyle);
        m_pCurrentStyle = pTempStyle;
        return m_pCurrentStyle;
    }

    std::shared_ptr<CFontStyle> CStyleManager::GetCurrentStyle()
    {
        if (!m_pCurrentStyle || m_bBrushWasChanged || m_bFontWasChanged ||
            m_oFontManager.m_bCurrentPickFontWasChanged || m_oFontManager.m_bCurrentPictFontStyleWasChanged)
        {
            auto pTempStyle = std::make_shared<CFontStyle>();

            pTempStyle->m_oBrush = m_oBrush;
            pTempStyle->m_oFont = m_oFontManager.m_oFont.m_oFont;
            pTempStyle->m_strPickFontName = m_oFontManager.m_strCurrentPickFont;
            pTempStyle->m_lPickFontStyle = m_oFontManager.m_lCurrentPictFontStyle;

            m_bBrushWasChanged = false;
            m_bFontWasChanged = false;
            m_oFontManager.m_bCurrentPickFontWasChanged = false;
            m_oFontManager.m_bCurrentPictFontStyleWasChanged = false;
            return GetStyle(pTempStyle);
        }

        return m_pCurrentStyle;
    }
}
