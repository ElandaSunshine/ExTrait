<?xml version="1.0"?>
<xsl:stylesheet version="3.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:xs="http://www.w3.org/2001/XMLSchema"
                    
                xmlns:doxls="elsa:doxls"
                xmlns:user="elsa:user">
    
    <!-- Piecing together the output before printing it -->
    <xsl:function name="user:pre_print_hook">
        <xsl:param name="document"/>

        <xsl:variable name="grouped_by_page">
            <xsl:for-each select="$document/*[local-name() = 'map' and *[@key = 'meta' and *[local-name() = 'map']/*[@key = 'key' and text() = 'group_by'] and *[local-name() = 'map']/*[@key = 'value' and text() = 'page']]]">
                <xsl:variable name="euid"  select="./*[@key = 'euid']/text()"/>
                <xsl:variable name="scope" select="./*[@key = 'scope']/text()"/>
                <xsl:variable name="page"  select="./*[@key = 'page']/text()"/>

                <group-target id="{$euid}" type="parent"><xsl:value-of select="./*[@key = 'name']/text()"/></group-target>

                <xsl:for-each select="$document/*">
                    <xsl:variable name="n_euid"  select="./*[@key = 'euid']/text()"/>
                    <xsl:variable name="n_scope" select="./*[@key = 'scope']/text()"/>
                    <xsl:variable name="n_page"  select="./*[@key = 'page']/text()"/>

                    <xsl:if test="$n_euid != $euid and $scope = $n_scope and $page = $n_page">
                        <group-target id="{$n_euid}" owner="{$euid}" type="child"><xsl:value-of select="./*[@key = 'name']/text()"/></group-target>
                    </xsl:if>
                </xsl:for-each>
            </xsl:for-each>
        </xsl:variable>        

        <xsl:for-each select="$document/*[local-name() = 'map']">
            <xsl:variable name="euid" select="current()/*[@key = 'euid']/text()"/>

            <xsl:if test="not($grouped_by_page/*[local-name() = 'group-target' and @id = $euid and @type = 'child'])">
                <map xmlns="http://www.w3.org/2005/xpath-functions">
                    <xsl:if test="$grouped_by_page/*[local-name() = 'group-target' and @id = $euid and @type = 'parent']">
                        <string key="refs">
                            <xsl:value-of select="string-join($grouped_by_page/*[local-name() = 'group-target' and @owner = $euid and @type = 'child']/text(), ',')"/>
                        </string>
                    </xsl:if>

                    <xsl:copy-of select="current()/*"/>
                </map>
            </xsl:if>
        </xsl:for-each>
    </xsl:function>

    <!-- Modifying keys in an object before adding them -->
    <xsl:function name="user:pre_element_hook">
        <xsl:param name="type"/>
        <xsl:param name="key"/>
        <xsl:param name="value"/>
        
        <xsl:choose>
            <xsl:when test="$key = 'tparams'">
                <xsl:sequence select="doxls:append('boolean', 'isTemplate', true())"/>
            </xsl:when>
            
            <xsl:when test="$key = 'properties'">
                <xsl:for-each select="$value/*">
                    <xsl:sequence select="doxls:append(local-name(), concat('property_', @key), text())"/>
                </xsl:for-each>
            </xsl:when>

            <xsl:when test="$key = 'details'">
                <xsl:if test="$value/ulink">
                    <xsl:variable name="content">
                        <xsl:analyze-string select="$value/ulink/text()" regex="[\?&amp;]([^=]+)=([^&amp;]+)" >
                            <xsl:matching-substring>
                                <xsl:value-of select="replace(regex-group(2), '%23', '#')" />
                            </xsl:matching-substring>
                        </xsl:analyze-string>
                    </xsl:variable>
                    
                    <xsl:sequence select="doxls:append('string', 'page', $content)"/>
                </xsl:if>

                <xsl:variable name="metasection" select="$value/*[local-name() = 'xrefsect' and starts-with(@id, 'internal_metadata')]"/>
                
                <xsl:if test="$metasection">
                    <xsl:variable name="content">
                        <xsl:for-each select="$metasection">
                            <xsl:if test="xreftitle/text() != 'ref_desc'">
                                <map xmlns="http://www.w3.org/2005/xpath-functions">
                                    <string key="key"><xsl:value-of select="xreftitle/text()"/></string>
                                    <string key="value"><xsl:value-of select="normalize-space(string-join(xrefdescription/para//text(), ''))"/></string>
                                </map>
                            </xsl:if>
                        </xsl:for-each>
                    </xsl:variable>

                    <xsl:sequence select="doxls:append('array', 'meta', $content)"/>

                    <xsl:variable name="ref_desc_obj" select="$metasection/*[local-name() = 'xreftitle' and text() = 'ref_desc']/parent::element()"/>

                    <xsl:if test="$ref_desc_obj">
                        <xsl:sequence select="doxls:append('string', 'brief2', normalize-space(string-join($ref_desc_obj/xrefdescription/para//text(), '')))"/>
                    </xsl:if>
                </xsl:if>

                <xsl:if test="$value/*[local-name() = 'ref']">
                    <xsl:sequence select="doxls:append('string', 'refs', string-join($value/*[local-name() = 'ref']/text(), ','))"/>
                </xsl:if>
            </xsl:when>

            <xsl:otherwise>
                <!-- The default appender -->
                <xsl:sequence select="doxls:append($type, $key, $value)"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:function>
</xsl:stylesheet>
