<?php
/**
 *	Node Wrapper
 *  Copyright (C) 2011  Korstiaan de Ridder <korstiaan [at] korstiaan.com>
 *
 *	This file is part of Node Wrapper.
 *
 *  Node Wrapper is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Node Wrapper is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Node Wrapper.  If not, see <http://www.gnu.org/licenses/>.
 */
namespace NodeWrapper;

use EntityBase\EntityBase;


class Node extends EntityBase implements NodeInterface
{
	const		TYPE			= 'node';
	
	private	$base = array(
		'language','nid','vid','title','log','status','comment','promote','sticky','created','changed','translate','revision_timestamp','revision_uid','is_new','type'
	);

	/**
	 * 
	 * Ctor.  
	 * 
	 * @throws 	\InvalidArgumentException		if node doesn't have bundle (type) defined or is invalid
	 * 
	 * @param 	\stdClass 		$node			the node
	 * @param 	string 			$language		the language to do the magic in
	 */
	public function __construct(\stdClass $node,$language = LANGUAGE_NONE)
	{
		if (!isset($node->type)) {
			throw new \InvalidArgumentException('Please set $node->type first.');
		}
		if (!self::isValidBundle($node->type)) {
			throw new \InvalidArgumentException("Invalid content type {$node->type}");
		}
		
		parent::__construct($node,$language);
	}
	
	/**
	 * 
	 * Save the node to db
	 * 
	 * @see 		NodeWrapper.NodeInterface::save()
	 * @see 		node_save()
	 * 
	 * @return		void
	 */
	public function save()
	{
		node_save($this->getEntity());
	}
	
	/**
	 *  
	 * @see EntityBase.EntityInterface::getEntityType()
	 */
	public function getEntityType() 	{ return self::TYPE; }

	
	/**
	 * 
	 * Returns node wrapper for node of given id
	 * 
	 * @throws 	\InvalidArgumentException	if param (nid) is not numeric
	 * 
	 * @param 	integer 		$nid
	 * @return	Node
	 */
	static function createByNid($nid) 
	{
		if (!is_numeric($nid)) {
			throw new \InvalidArgumentException('Node id should be numeric');
		}
		static $ret = array();
		if (!isset($ret[$nid])) {
			$ret[$nid] = new static(node_load($nid));
		}
		return $ret[$nid];
	}
	
	/**
	 * 
	 * Returns wrapper for a node of given type (bundle).
	 * 
	 * @param 	string 	$bundle  
	 * @return	Node 
	 */
	static function createByType($bundle) 
	{
		$node = new \stdClass();
		$node->type = $bundle;
		return new static($node);
	}
	
	/**
	 * 
	 * Checks if given bundle (content type) is valid.
	 * 
	 * @param 	string 	$bundle
	 * @return	boolean
	 */
	static function isValidBundle($bundle) 
	{
		return in_array($bundle,array_keys((array)field_info_bundles(self::TYPE)));
	}
	/**
	 * @see EntityBase.EntityBase::getBundleName()
	 */
	protected function getBundleName() 	{ return $this->getEntity()->type; }
	/**
	 * @see EntityBase.EntityBase::getBaseFields()
	 */
	protected function getBaseFields()	{ return (array)$this->base; }
	
}