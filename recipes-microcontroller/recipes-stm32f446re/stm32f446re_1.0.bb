DESCRIPTION = "Build stm32f446re image"
LICENSE = "CLOSED"
SRC_URI = "file://stm32f446re"

DEPENDS = "gcc-arm-none-eabi-native"

S = "${WORKDIR}/stm32f446re/driver_developtment_NO_IDE"

do_compile() {
    cd ${S}
    oe_runmake 
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 hello ${D}${bindir}/
}