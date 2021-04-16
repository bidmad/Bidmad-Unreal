# Unreal GDPR Guide [KOR]

# **유럽사용자 동의 요청(GDPR)**

Bidmad와 연동된 AdNetwork SDK에서 제공하는 GDPR(EU 온라인 개인정보보호지침 및 개인정보 보호법)에 대한 Interface를 제공하고 있습니다.Ad Network에 따라 인터페이스가 상이한 부분이 있어 총 두 가지 Interface를 제공하고 있으므로 사용하시는 네트워크에 맞는 Interface를 사용 바랍니다.

- 일부 네트워크의 경우 GDPR Interface를 제공하지 않는 경우가 있으므로 GDPR 적용 전에 문의를 부탁 드립니다.

---

### **Google GDPR Interface**

Google에서는 Funding Choices 플랫폼을 통해 사용자 동의 팝업을 설정하고 UMP SDK를 통해 사용자에게 노출 시킵니다.Google GDPR Interface는 Google(Admob / Admanager)에서 제공하는 UMP SDK에 대한 Wrapper Interface 입니다.Bidmad 이전에 UMP SDK를 통해 Google GDPR을 적용하였다면, Bidmad에서 제공하는 Interface로 변경하여 작업을 하지 않아도 괜찮습니다.

Funding Choices에서 사용자 동의 팝업 양식 생성 후 아래 사용법에 따라 사용자 동의 요청을 수행하세요.

### 초기 **GDPR 인터페이스 세팅**

Google GDPR Consent Interface를 actor class에 추가하세요, 그리고 Listener 세팅을 하십시오.

![./UnrealGDPRGuide/_2021-04-16__2.42.46.png](./UnrealGDPRGuide/_2021-04-16__2.42.46.png)

### **Google GDPR은 다음과 같은 스텝을 거칩니다.**

```
1. Google GDPR SDK에게 동의 팝업을 요청합니다.
2. 동의 팝업 폼 로드를 요청합니다.
3. GDPR 동의가 필요한지에 대해 확인하고 동의 팝업 폼을 사용자에게 보여줍니다.
4. 동의 팝업 폼의 결과를 받습니다.
```

### **1.** 동의 팝업 요청

![./UnrealGDPRGuide/_2021-04-16__2.46.14.png](./UnrealGDPRGuide/_2021-04-16__2.46.14.png)

### **2. 동의 팝업 폼 로드 요청**

동의 팝업을 요청한 이후, "On Consent Info Update Success" 콜백을 받을 것입니다. 그에 따라, 폼을 로드할 수 있는지 체크한 이후, "Load Form"을 수행하십시오

![./UnrealGDPRGuide/_2021-04-16__2.47.45.png](./UnrealGDPRGuide/_2021-04-16__2.47.45.png)

### **3. GDPR 동의 필요 여부 확인 및 동의 팝업 폼 디스플레이**

동의 폼이 로드가 된 이후, 사용자 동의가 필요한지를 먼저 확인하시는 것을 추천드립니다. 동의 확인 필요 여부 및 동의를 이미 받았는지에 대한 정보를 "Get Consent Status"로 받아온 뒤, 만약 1 값이 리턴된 경우, "Show Form"을 콜해, 사용자에게 동의 폼을 디스플레이 하십시오.

![./UnrealGDPRGuide/_2021-04-16__3.24.39.png](./UnrealGDPRGuide/_2021-04-16__3.24.39.png)

### **4. 동의 팝업 폼 결과 확인**

유저의 동의 프로세스가 완료된 이후, "Consent Form Dismissed" 콜백을 받을 때, 만약 error message가 null 일 경우, 사용자가 '동의' 혹은 '비동의'를 눌렀음을 알 수 있습니다.

![./UnrealGDPRGuide/_2021-04-16__3.31.47.png](./UnrealGDPRGuide/_2021-04-16__3.31.47.png)

### 요청 및 폼 로드 실패 콜백

· 동의 팝업 요청 실패

![./UnrealGDPRGuide/_2021-04-16__3.34.31.png](./UnrealGDPRGuide/_2021-04-16__3.34.31.png)

· 동의 팝업 폼 로드 실패

![./UnrealGDPRGuide/_2021-04-16__3.35.09.png](./UnrealGDPRGuide/_2021-04-16__3.35.09.png)

### 초기 디버깅 및 테스트 세팅

1. 위 세팅이 모두 완료된 이후, GDPR for Google 팝업 요청을 실행하십시오
2. 다음과 같은 로그가 콘솔에 기록될 것입니다.
    - `iOS: <UMP SDK> To enable debug mode for this device, set: UMPDebugSettings.testDeviceIdentifiers = @[ @"Test Device Unique ID" ];`
    - `AOS: UserMessagingPlatform: Use new ConsentDebugSettings.Builder().addTestDeviceHashedId("TEST-DEVICE-HASHED-ID") to set this as a debug device.`
3. 주어진 테스트 디바이스 고유 ID를 삽입한 다음 코드를 초기 세팅에 포함시키십시오

    ![./UnrealGDPRGuide/_2021-04-16__3.38.59.png](./UnrealGDPRGuide/_2021-04-16__3.38.59.png)

---

### **GDPR Interface**

Google(Admob / Admanager)를 제외한 타 Ad Network에서 제공하는 GDPR Interface에 대한 대응 Interface입니다.타 Ad Network에서는 광고 요청 시 사용자 동의 결과(동의 / 비동의)에 대한 값을 SDK에 전달하도록 Interface가 구성되어 있으며 Bidmad에서 제공하는 GDPR Interface는 사용자 동의 결과를 각 Ad Network의 SDK에 전달하는 역할을 수행합니다.

GDPR Interface를 사용하고자 하시는 경우 사용자 동의를 받기 위한 팝업을 개발 하신 후 팝업 결과에 따라 GDPR Interface를 호출바랍니다.

### **GDPR 동의 및 지역 설정 (사용자 동의의 경우, true / EEA의 경우, true)  및 GDPR 세팅 값.**

![./UnrealGDPRGuide/_2021-04-16__3.57.34.png](./UnrealGDPRGuide/_2021-04-16__3.57.34.png)

### **GDPR Setting 값 (GDPRConsentStatus: Int)**

`GDPRConsentStatusYES = 1,
GDPRConsentStatusNO = 0,
GDPRConsentStatusUNKNOWN = -1,
GDPRConsentStatusUNUSE = -2`
