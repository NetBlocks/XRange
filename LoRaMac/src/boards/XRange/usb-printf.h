#ifndef __USB_PRINTF__
#define __USB_PRINTF__

void vcom_Send(const char *format, ...);

#ifdef USE_USB_CDC
    #define PRINTF(...)     vcom_Send(__VA_ARGS__)
#else
    #define PRINTF(...)
#endif

#endif
