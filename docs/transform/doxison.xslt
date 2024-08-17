<?xml version="1.0"?>
<xsl:stylesheet version="3.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:xs="http://www.w3.org/2001/XMLSchema"
                xmlns:map="http://www.w3.org/2005/xpath-functions/map"

                xmlns:doxls="elsa:doxls"
                xmlns:user="elsa:user">
    
    <!--  *********************************************** INTERNAL ************************************************  -->
    <xsl:template match="text()" />
    <xsl:variable name="config" select="parse-json(unparsed-text('config.json'))"/>
    <xsl:import href="user.xslt"/>
    <xsl:output method="text" encoding="UTF-8"/>

    <xsl:function name="doxls:append" visibility="public">
        <xsl:param name="type"/>
        <xsl:param name="key"/>
        <xsl:param name="value"/>

        <xsl:element name="{$type}" namespace="http://www.w3.org/2005/xpath-functions">
            <xsl:if test="$key and not(ends-with($key, '#'))">
                <xsl:attribute name="key" select="if (contains($key, '.')) then tokenize($key, '\.')[last()] else $key"/>
            </xsl:if>
            <xsl:copy-of select="$value"/>
        </xsl:element>
    </xsl:function>

    <xsl:function name="doxls:add_key" visibility="private">
        <xsl:param name="type"/>
        <xsl:param name="key"/>
        <xsl:param name="value"/>

        <xsl:if test="not($key = $config('ignoredFields'))">
            <xsl:sequence select="user:pre_element_hook($type, $key, $value)"/>
        </xsl:if>
    </xsl:function>

    <!--  ******************************************* ENTITY TEMPLATES ********************************************  -->
    <!-- For doxygen types: struct, class, union -->
    <xsl:template name="process_content" visibility="private">
        <xsl:param name="namespace"/>
        <xsl:param name="member"/>
        <xsl:param name="groups"/>

        <!-- processing top level struct entities -->
        <xsl:for-each select="./*[local-name() = 'innerclass']">
            <xsl:variable name="cs_name"  select="text()"/>
            <xsl:variable name="cs_index" select="concat(@refid, '.xml')"/>
            <xsl:variable name="cs_data">
                <xsl:copy-of select="document(concat($config('workingDir'), $cs_index))"/>
            </xsl:variable>
            
            <xsl:for-each select="$cs_data/doxygen/compounddef">
                <map xmlns="http://www.w3.org/2005/xpath-functions">
                    <string key="name"><xsl:value-of  select="if (starts-with($cs_name, concat($namespace, '::'))) then substring-after($cs_name, concat($namespace, '::')) else $cs_name"/></string>
                    <string key="kind"><xsl:value-of  select="@kind"/></string>
                    <string key="scope"><xsl:value-of select="$namespace"/></string>
                    <string key="fqn"><xsl:value-of   select="compoundname/text()"/></string>

                    <xsl:variable name="groups_def">
                        <xsl:for-each select="distinct-values($groups/*[@fqn = current()/compoundname/text() and @kind = 'class']/@group)">
                            <string><xsl:value-of select="."/></string>
                        </xsl:for-each>
                    </xsl:variable>

                    <xsl:sequence select="doxls:add_key('array', 'groups', $groups_def)"/>
                    <xsl:sequence select="doxls:add_key('string', 'visibility', @prot)"/>

                    <xsl:if test="basecompoundref">
                        <xsl:if test="not('bases' = $config('ignoredFields'))">
                            <array key="bases">
                                <xsl:for-each select="*[local-name() = 'basecompoundref']">
                                    <map>
                                        <xsl:sequence select="doxls:add_key('string', 'bases.type',       text())"/>
                                        <xsl:sequence select="doxls:add_key('string', 'bases.visibility', @prot)"/>
                                        <xsl:sequence select="doxls:add_key('string', 'bases.virtual',    @virt)"/>
                                    </map>
                                </xsl:for-each>
                            </array>
                        </xsl:if>
                    </xsl:if>

                    <xsl:if test="not('brief' = $config('ignoredFields'))">
                        <xsl:variable name="brief" select="normalize-space(string-join(briefdescription//text(), ''))"/>
                    
                        <xsl:if test="$brief">
                            <string key="brief">
                                <xsl:value-of select="$brief"/>
                            </string>
                        </xsl:if>
                    </xsl:if>

                    <xsl:variable name="details">
                        <xsl:sequence select="user:parse_details(detaileddescription/para)"/>
                    </xsl:variable>

                    <xsl:call-template name="get_element_type">
                        <xsl:with-param name="parent"   select="'xsl.details'"/>
                        <xsl:with-param name="children" select="$details"/>
                    </xsl:call-template>

                    <xsl:variable name="tparams">
                        <xsl:for-each select="./templateparamlist/param">
                            <xsl:variable name="key" select="declname/text()"/>
                            
                            <map>
                                <xsl:if test="$key">
                                    <string key="name"><xsl:value-of select="$key"/></string>
                                </xsl:if>
                                
                                <string key="type"><xsl:value-of select="type//text()"/></string>
                            </map>
                        </xsl:for-each>
                    </xsl:variable>
                    <xsl:sequence select="doxls:add_key('array', 'tparams', $tparams)"/>
                </map>


                <xsl:call-template name="process_content">
                    <xsl:with-param name="namespace" select="$cs_name"/>
                    <xsl:with-param name="member"    select="true()"/>
                    <xsl:with-param name="groups"    select="$groups"/>
                </xsl:call-template>
            </xsl:for-each>
        </xsl:for-each>
        
        <!-- processing other entities -->
        <xsl:for-each select="./*[local-name() = 'sectiondef']/*[local-name() = 'memberdef']">
            <map xmlns="http://www.w3.org/2005/xpath-functions">
                <string key="name" ><xsl:value-of select="name/text()"/></string>
                <string key="kind" ><xsl:value-of select="@kind"/></string>
                <string key="scope"><xsl:value-of select="$namespace"/></string>
                <string key="fqn"  ><xsl:value-of select="qualifiedname/text()"/></string>

                <xsl:variable name="groups_def">
                    <xsl:for-each select="distinct-values($groups/*[@fqn = current()/qualifiedname/text() and @kind = current()/@kind]/@group)">
                        <string><xsl:value-of select="."/></string>
                    </xsl:for-each>
                </xsl:variable>

                <xsl:sequence select="doxls:add_key('array',  'groups',     $groups_def)"/>
                <xsl:sequence select="doxls:add_key('string', 'visibility', @prot)"/>

                <xsl:if test="not('brief' = $config('ignoredFields'))">
                    <xsl:variable name="brief" select="normalize-space(string-join(briefdescription//text(), ''))"/>

                    <xsl:if test="$brief">
                        <xsl:sequence select="doxls:add_key('string', 'brief', $brief)"/>
                    </xsl:if>
                </xsl:if>
                
                <xsl:variable name="details">
                    <xsl:sequence select="user:parse_details(detaileddescription/para)"/>
                </xsl:variable>
                
                <xsl:call-template name="get_element_type">
                    <xsl:with-param name="parent"   select="'xsl.details'"/>
                    <xsl:with-param name="children" select="$details"/>
                </xsl:call-template>
                
                <xsl:if test="@kind = ('struct', 'class', 'union', 'variable', 'typedef', 'function')">
                    <xsl:variable name="tparams">
                        <xsl:for-each select="./templateparamlist/param">
                            <xsl:variable name="key" select="declname/text()"/>
                            
                            <map>
                                <xsl:if test="$key">
                                    <string key="name"><xsl:value-of select="$key"/></string>
                                </xsl:if>
                                
                                <string key="type"><xsl:value-of select="type//text()"/></string>
                            </map>
                        </xsl:for-each>
                    </xsl:variable>
                    <xsl:sequence select="doxls:add_key('array', 'tparams', $tparams)"/>
                </xsl:if>
                
                <xsl:if test="@kind = 'variable' and not('properties' = $config('ignoredFields'))">
                    <xsl:variable name="properties_map">
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.static',    if (@static    = 'yes') then true() else false())"/>
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.constexpr', if (@constexpr = 'yes') then true() else false())"/>
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.inline',    if (@inline    = 'yes') then true() else false())"/>
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.const',     if (@const     = 'yes' or @constexpr = 'yes') then true() else false())"/>
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.member',    $member)"/>
                    </xsl:variable>

                    <xsl:sequence select="doxls:add_key('map', 'properties', $properties_map)"/>
                </xsl:if>
                
                <xsl:if test="@kind = 'function'">
                    <xsl:if test="./param and not('params' = $config('ignoredFields'))">
                        <array key="parameters">
                            <xsl:for-each select="./param">
                                <xsl:variable name="key" select="declname/text()"/>
                                
                                <map>
                                    <xsl:if test="$key">
                                        <string key="name"><xsl:value-of select="$key"/></string>
                                    </xsl:if>
                                    
                                    <string key="type"><xsl:value-of select="type//text()"/></string>
                                </map>
                            </xsl:for-each>
                        </array>
                    </xsl:if>
                    
                    <xsl:variable name="properties_map">
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.static',    if (@static    = 'yes') then true() else false())"/>
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.constexpr', if (@constexpr = 'yes') then true() else false())"/>
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.explicit',  if (@explicit  = 'yes') then true() else false())"/>
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.inline',    if (@inline    = 'yes') then true() else false())"/>
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.noexcept',  if (@noexcept  = 'yes') then true() else false())"/>
                        <xsl:sequence select="doxls:add_key('boolean', 'properties.member',    $member)"/>
                        <xsl:sequence select="doxls:add_key('string',  'properties.virtual',   @virt)"/>

                        <xsl:variable name="properties_qualifiers">
                            <xsl:sequence select="doxls:add_key('boolean', 'properties.qualified.const',    if (@const    = 'yes') then true() else false())"/>
                            <xsl:sequence select="doxls:add_key('boolean', 'properties.qualified.volatile', if (@volatile = 'yes') then true() else false())"/>
                            
                            <xsl:choose>
                                <xsl:when test="@refqual = 'lvalue'">
                                    <xsl:sequence select="doxls:add_key('boolean', 'properties.qualified.lvalue', true())"/>
                                    <xsl:sequence select="doxls:add_key('boolean', 'properties.qualified.rvalue', false())"/>
                                </xsl:when>
                                <xsl:when test="@refqual = 'rvalue'">
                                    <xsl:sequence select="doxls:add_key('boolean', 'properties.qualified.lvalue', false())"/>
                                    <xsl:sequence select="doxls:add_key('boolean', 'properties.qualified.rvalue', true())"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <xsl:sequence select="doxls:add_key('boolean', 'properties.qualified.rvalue', false())"/>
                                    <xsl:sequence select="doxls:add_key('boolean', 'properties.qualified.lvalue', false())"/>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:variable>

                        <xsl:sequence select="doxls:add_key('map', 'properties.qualifiers', $properties_qualifiers)"/>
                    </xsl:variable>

                    <xsl:sequence select="doxls:add_key('map', 'properties', $properties_map)"/>
                </xsl:if>
            </map>
        </xsl:for-each>
    </xsl:template>
    
    
    
    <!-- =========================================================================================================== -->
    <!-- Transform all root compounds -->
    <xsl:template name="main" visibility="private">
        <xsl:variable name="index_file">
            <xsl:copy-of select="document(concat($config('workingDir'), 'index.xml'))"/>
        </xsl:variable>

        <xsl:variable name="groups">
            <xsl:for-each select="$index_file/doxygenindex/compound[@kind='group']">
                <xsl:variable name="gp_index" select="concat(@refid, '.xml')"/>
                <xsl:variable name="gp_data">
                    <xsl:copy-of select="document(concat($config('workingDir'), $gp_index))"/>
                </xsl:variable>
                <xsl:variable name="gp_name" select="name/text()"/>

                <xsl:for-each select="$gp_data/doxygen/compounddef/*[local-name() = 'innerclass']">
                    <member kind="class" fqn="{text()}" group="{$gp_name}"/>
                </xsl:for-each>

                <xsl:for-each select="$gp_data/doxygen/compounddef/*[local-name() = 'sectiondef']/*[local-name() = 'memberdef']">
                    <member kind="{@kind}" fqn="{qualifiedname/text()}" group="{$gp_name}"/>
                </xsl:for-each>
            </xsl:for-each>
        </xsl:variable>

        <xsl:variable name="json">
            <array xmlns="http://www.w3.org/2005/xpath-functions">
                <xsl:for-each select="$index_file/doxygenindex/compound[@kind='namespace']">
                    <xsl:variable name="ns_name"  select="name/text()"/>
                    <xsl:variable name="ns_index" select="concat(@refid, '.xml')"/>
                    <xsl:variable name="ns_data">
                        <xsl:copy-of select="document(concat($config('workingDir'), $ns_index))"/>
                    </xsl:variable>
                    
                    <xsl:for-each select="$ns_data/doxygen/compounddef">
                        <xsl:call-template name="process_content">
                            <xsl:with-param name="namespace" select="$ns_name"/>
                            <xsl:with-param name="member"    select="false()"/>
                            <xsl:with-param name="groups"    select="$groups"/>
                        </xsl:call-template>
                    </xsl:for-each>
                </xsl:for-each>
            </array>
        </xsl:variable>
        
        <xsl:value-of select="xml-to-json($json)"/>
    </xsl:template>
    
    <xsl:template name="get_element_type">
        <xsl:param name="parent"/>
        <xsl:param name="children"/>
        <xsl:param name="isParentArray" select="false()"/>
        
        <xsl:for-each select="$children/DocElement">
            <xsl:choose>
                <xsl:when test="@type = ('string', 'boolean', 'number')">
                    <xsl:if test="normalize-space(text())">
                        <xsl:sequence select="doxls:add_key(@type, concat($parent, '.', @key), text())"/>
                    </xsl:if>
                </xsl:when>
                <xsl:when test="@type = ('array', 'map')">
                    <xsl:variable name="id" select="if ($isParentArray) then concat($parent, '.#') else concat($parent, '.', @key)"/>

                    <xsl:variable name="children_nodes">
                        <xsl:call-template name="get_element_type">
                            <xsl:with-param name="parent"        select="$id"/>
                            <xsl:with-param name="children"      select="."/>
                            <xsl:with-param name="isParentArray" select="@type = 'array'"/>
                        </xsl:call-template>
                    </xsl:variable>

                    <xsl:sequence select="doxls:add_key(@type, $id, $children_nodes)"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:message terminate="yes">Invalid json type "<xsl:value-of select="@type"/>", allowed are string, number, boolean, array or map</xsl:message>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:for-each>
    </xsl:template>
 </xsl:stylesheet>
