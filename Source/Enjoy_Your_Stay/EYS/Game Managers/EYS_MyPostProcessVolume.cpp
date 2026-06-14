// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MyPostProcessVolume.h"

AEYS_MyPostProcessVolume::AEYS_MyPostProcessVolume()
{
	// Varsayılan olarak bu volume haritanın neresinde durursa dursun her yeri etkilesin gulum
	bUnbound = false;
	Priority = 10.0f; // Standart PP'lerin üstüne çıksın diye yüksek öncelik ke!
	bEnabled = true;  // İlk başta aktif olsun ama efekt gücü constructor'da sıfırlanacak gulum

	Settings.bOverride_SceneFringeIntensity = true;
	Settings.SceneFringeIntensity = 0.0f;

	Settings.bOverride_FilmGrainIntensity = true;
	Settings.FilmGrainIntensity = 0.0f;

	Settings.bOverride_VignetteIntensity = true;
	Settings.VignetteIntensity = 0.0f;
}
void AEYS_MyPostProcessVolume::PlayJumpscareGlitch()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(GlitchTimerHandle);
	}

	// Hacmi sınırsız yapıyoruz ki oyuncu otelin neresinde olursa olsun tüm ekranı kaplasın ke!
	bUnbound = true;
	CurrentGlitchIntensity = 0.0f;

	// 0.02 saniyede bir sinsi fonksiyonu çağırıp ekranı yırtmaya başlıyoruz gulum!
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(GlitchTimerHandle, this, &AEYS_MyPostProcessVolume::UpdateGlitchSettings, 0.02f, true);
	}
}

void AEYS_MyPostProcessVolume::UpdateGlitchSettings()
{
	CurrentGlitchIntensity += 0.02f;

	FPostProcessSettings& PP = Settings;

	// ⏳ 1. AŞAMA: İLK 3.5 SANİYE - EKRAN VAHŞİ VE ULTRA HIZLI YIRTILIYOR KE!
	if (CurrentGlitchIntensity <= 3.5f)
	{
		// Sinüsün frekansı hâlâ kudurmuş nizamda (* 12.0f); o vahşi hızı asla kaybetmiyoruz gulum!
		float Wave = FMath::Abs(FMath::Sin(CurrentGlitchIntensity * 12.0f));

		// 🎥 CHROMATIC ABERRATION: Renkler mermi gibi kopuyor ke
		PP.bOverride_SceneFringeIntensity = true;
		PP.SceneFringeIntensity = Wave * 35.0f;

		// ⚡ GRAIN: Karıncalanma çılgınlar gibi yanıp sönüyor
		PP.bOverride_FilmGrainIntensity = true;
		PP.FilmGrainIntensity = Wave * 2.0f;
		PP.bOverride_FilmGrainTexelSize = true;
		PP.FilmGrainTexelSize = Wave * 7.0f;
		// 👁️ VIGNETTE: Kenarlar feci hızlı bir nabız gibi daralıyor gulum ke
		PP.bOverride_VignetteIntensity = true;
		PP.VignetteIntensity = Wave * 0.4f;

	}
	// 🌑 2. AŞAMA: 3.5. SANİYEDEN 5. SANİYEYE KADAR (SON 1.5 SANİYE) - HIZLI KARARMA KE!
	else if (CurrentGlitchIntensity > 3.5f && CurrentGlitchIntensity <= 5.0f)
	{
		// Kalan 1.5 saniyelik kısa ve sinsi sürede ekranı pürüzsüzce karanlığa gömüyoruz gulum.
		// 3.5 ile 5.0 saniye arası için Lerp alfası (oranı) hesapla ke:
		float Alpha = (CurrentGlitchIntensity - 3.5f) / 1.5f;

		// Yırtılmalar sönümlenirken zifiri karanlık tüm ekranı yutuyor ke gulum:
		PP.SceneFringeIntensity = FMath::Lerp(PP.SceneFringeIntensity, 0.0f, Alpha);
		PP.FilmGrainIntensity = FMath::Lerp(PP.FilmGrainIntensity, 0.0f, Alpha);
		PP.FilmGrainTexelSize = FMath::Lerp(PP.FilmGrainTexelSize, 0.0f, Alpha);
		// Vignette değerini 5.0f'e vurarak ekranı zifiri kapkara bir deliğe çeviriyoruz!
		PP.bOverride_VignetteIntensity = true;
		PP.VignetteIntensity = FMath::Lerp(PP.VignetteIntensity, 10.0f, Alpha);
		PP.bOverride_AutoExposureMinBrightness = true;
		PP.bOverride_AutoExposureMaxBrightness = true;
		PP.AutoExposureMinBrightness = FMath::Lerp(PP.AutoExposureMinBrightness, 0.0f, Alpha);
		PP.AutoExposureMaxBrightness = FMath::Lerp(PP.AutoExposureMaxBrightness, 0.0f, Alpha);
	}
	else
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(GlitchTimerHandle);
		}
		PP.AutoExposureMinBrightness = 0.0f;
		PP.AutoExposureMaxBrightness = 0.0f;
		

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "BABA YAGA 5 SANIYEDE ISINI BITIRDI, OYUN BITTI GULUM!");
	}
}
