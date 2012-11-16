<?php


// need to integrate this in the lazy_admin.callback.php




chdir($_SERVER['DOCUMENT_ROOT']);
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once DRUPAL_ROOT . '/includes/common.inc';
require_once DRUPAL_ROOT . '/includes/module.inc';
require_once DRUPAL_ROOT . '/includes/unicode.inc';

drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE); // Faster alternative to bootstrap?

// get all posted data
$value = trim($_POST['text']);
$lang = $_POST['lang'];

$results = babylon_translate_seek($value, $lang);
$output = theme_results($results);
drupal_json_output($output);




/*
* Pimped version of _locale_translate_seek
 */
function babylon_translate_seek($string, $lang){
  $output = '';
  $query['string'] = $string;
  $query['language'] = $lang;
  // We have at least one criterion to match

  $sql_query = db_select('locales_source', 's');
  $sql_query->leftJoin('locales_target', 't', 't.lid = s.lid');
  $sql_query->fields('s', array('source', 'location', 'context', 'lid', 'textgroup'));
  $sql_query->fields('t', array('translation', 'language'));
      $condition = db_or()
        ->condition('s.source', '%' . db_like($query['string']) . '%', 'LIKE');
      if ($query['language'] != 'en') {
        // Only search in translations if the language is not forced to English.
        $condition->condition('t.translation', '%' . db_like($query['string']) . '%', 'LIKE');
      }
      $sql_query->condition($condition);

  $limit_language = NULL;
  if ($query['language'] != 'en' && $query['language'] != 'all') {
    $sql_query->condition('language', $query['language']);
    $limit_language = $query['language'];
  }

  $sql_query = $sql_query->extend('PagerDefault')->limit(25);
  $locales = $sql_query->execute()->fetchAll();

  foreach((array)$locales as $locale) {
    $strings[$locale->lid] = $locale->source;
  }
  return $strings;
}

function theme_results($results){
  // as we don't want to fully bootstrap, we build html ourselves
  foreach($results as $lid => $string){
    $items[] = '<a href="/admin/config/regional/translate/edit/'. $lid .'">' . substr($string, 0,100) . '</a>';
  }
  $output = '<div class="translation_options"><ul>';
  foreach($items as $item){
    $output .= '<li>' . $item . '</li>';
  }
  $output .= '</ul></div>';
  return $output;
}