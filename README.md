Node Wrapper for Drupal 7.x
========================
Drupal module which provides simple access to a node's fields.


Requirements
--------------------------------

* Drupal 7.x
* PHP 5.3.2 or higher
* Namespace Autoload (https://github.com/korstiaan/nsautoload)
* Entity Base (https://github.com/korstiaan/entitybase)

Setup / Initial Installation
--------------------------------

Install it as a normal Drupal module. This means downloading (or git clone'ing) it to site/all/modules and enabling it on "admin/modules/list".

If you're using Voiture (http://voiture.hoppinger.com) just add "nodewrapper" to cnf/shared/modules.php


Usage
--------------------------------

* Initializing:

$foo = new NodeWrapper\Node($node);
$foo = NodeWrapper\Node::createByNid($node->nid);
$foo = NodeWrapper\Node::createByType('page');

* get/set field value:

$value = $foo->get('field_bar');
$foo->set('field_crux','lipsum');

Look at the inline (phpdoc) documentation for more info.
 