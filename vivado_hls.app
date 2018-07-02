<project xmlns="com.autoesl.autopilot.project" name="hls4gtl" top="algos">
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow askAgain="false" name="csim" csimMode="0" lastCsimMode="0" compiler="true"/>
    </Simulation>
    <files xmlns="">
        <file name="../tb/algos_test.cpp" sc="0" tb="1" cflags=" -I../../../include "/>
        <file name="hls4gtl/include/templates.h" sc="0" tb="false" cflags=""/>
        <file name="hls4gtl/include/requirements.h" sc="0" tb="false" cflags=""/>
        <file name="hls4gtl/include/pt_comp.h" sc="0" tb="false" cflags=""/>
        <file name="hls4gtl/src/pt_comp.cpp" sc="0" tb="false" cflags="-Ihls4gtl/include"/>
        <file name="hls4gtl/include/obj.h" sc="0" tb="false" cflags=""/>
        <file name="hls4gtl/include/eta_comp.h" sc="0" tb="false" cflags=""/>
        <file name="hls4gtl/src/eta_comp.cpp" sc="0" tb="false" cflags="-Ihls4gtl/include"/>
        <file name="hls4gtl/include/definitions.h" sc="0" tb="false" cflags=""/>
        <file name="hls4gtl/include/comp.h" sc="0" tb="false" cflags=""/>
        <file name="hls4gtl/src/comp.cpp" sc="0" tb="false" cflags="-Ihls4gtl/include"/>
        <file name="hls4gtl/include/algos.h" sc="0" tb="false" cflags=""/>
        <file name="hls4gtl/src/algos.cpp" sc="0" tb="false" cflags="-Ihls4gtl/include"/>
    </files>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

