<?php

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
<<<<<<< HEAD
$output = theme_results($results, $_POST['url']);
=======
$output = theme_results($results);
>>>>>>> d66f6decb4dfd6e286e7f75462dd33536bba89bf
header("Cache-Control: no-cache, must-revalidate, max-age=0");
drupal_json_output($output);




/*
* Pimped version of _locale_translate_seek
 */
function babylon_translate_seek($string = '', $lang = 'en'){
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
//  if ($query['language'] != 'en' && $query['language'] != 'all') {
////    $sql_query->condition('language', $query['language']);
//    $limit_language = $query['language'];
//  }

  $sql_query = $sql_query->extend('PagerDefault')->limit(10);
  $locales = $sql_query->execute()->fetchAll();

  foreach((array)$locales as $locale) {
    $strings[$locale->lid] = $locale->source;
  }

  return $strings;
}

function theme_results($results, $url = ''){
  if(!empty($url)){
    $url = '?destination=' . $url;
  }
  if(!empty($results)){
    // as we don't want to fully bootstrap, we build html ourselves
    foreach((array)$results as $lid => $string){
      $items[] = '<a href="/admin/config/regional/translate/edit/'. $lid . $url . '">' . substr($string, 0,100) . '</a>';
    }
  }
  else{
    $items[] = '<a>'. t('No results found') . '</a>';
  }
  $output = '<ul>';
  foreach((array)$items as $item){
    $output .= '<li>' . $item . '</li>';
  }
  $output .= '</ul>';
  return $output;
}