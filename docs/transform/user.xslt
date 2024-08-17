<?xml version="1.0"?>
<xsl:stylesheet version="3.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:xs="http://www.w3.org/2001/XMLSchema"
                    
                xmlns:doxls="elsa:doxls"
                xmlns:user="elsa:user">
    
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

            <xsl:otherwise>
                <!-- The default appender -->
                <xsl:sequence select="doxls:append($type, $key, $value)"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:function>
    
    <xsl:function name="user:parse_details">
        <xsl:param name="context"/>

        <xsl:if test="$context/ulink">
            <DocElement key="page" type="string">
                <xsl:analyze-string select="$context/ulink/text()" regex="[\?&amp;]([^=]+)=([^&amp;]+)" >
                    <xsl:matching-substring>
                        <xsl:value-of select="replace(regex-group(2), '%23', '#')" />
                    </xsl:matching-substring>
                </xsl:analyze-string>
            </DocElement>
        </xsl:if>
        
        <xsl:variable name="metasection" select="$context/*[local-name() = 'xrefsect' and starts-with(@id, 'internal_metadata')]"/>
        
        <xsl:if test="$metasection">
            <DocElement key="meta" type="array">
                <xsl:for-each select="$metasection">
                    <DocElement type="map">
                        <DocElement type="string" key="key"><xsl:value-of select="xreftitle/text()"/></DocElement>
                        <DocElement type="string" key="value"><xsl:value-of select="normalize-space(string-join(xrefdescription/para//text(), ''))"/></DocElement>
                    </DocElement>
                </xsl:for-each>
            </DocElement>
        </xsl:if>
        
        <xsl:if test="$context/*[local-name() = 'ref']">
            <DocElement key="refs" type="string">
                <xsl:value-of select="string-join($context/*[local-name() = 'ref']/text(), ',')"/>
            </DocElement>
        </xsl:if>
    </xsl:function>
</xsl:stylesheet>
