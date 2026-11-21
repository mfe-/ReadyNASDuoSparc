// Faux DOM minimal : chaque sélecteur renvoie toujours le même objet, qui enregistre ce qu'on y écrit.
const fs = require('fs'), els = {};
const mk = () => ({ style:{}, dataset:{}, children:[], classList:{ set:new Set(), toggle(c,on){ on?this.set.add(c):this.set.delete(c); }, add(c){this.set.add(c)}, remove(c){this.set.delete(c)} }, querySelector:()=>mk(), textContent:'', innerHTML:'', title:'' });
const $el = s => els[s] || (els[s] = mk());
global.navigator = { languages: ['fr-FR', 'fr'] };
global.document = { querySelector:$el, querySelectorAll:()=>[], addEventListener(){}, body:$el('body'), visibilityState:'hidden', title:'' };
global.performance = { now:()=>0 }; global.fetch = async()=>{ throw new Error('pas de réseau'); };
global.setTimeout = ()=>0; global.clearTimeout = ()=>{};
eval(fs.readFileSync(process.argv[2], 'utf8') + '\nglobal.render = render; global.setLang = l => { LANG = l; }; global.getLang = () => LANG; global.I18N = I18N; global.tr = t;');
const hideWarning = $el('#alarmx').onclick;   // le gestionnaire est posé au chargement de la page
const strip = h => h.replace(/<[^>]+>/g, ' ').replace(/\s+/g, ' ').trim();
let fail = 0; const check = (name, cond) => { console.log((cond ? 'ok   ' : 'FAIL ') + name); if (!cond) fail++; };
for (const f of process.argv.slice(3)) {
  for (const k in els) if (k !== 'body') delete els[k];
  const s = JSON.parse(fs.readFileSync(f, 'utf8')); render(s);
  console.log('--- ' + f.split('/').pop());
  console.log('  sous-titre :', $el('#sub').textContent, '| sans écran :', $el('body').classList.set.has('nolcd'));
  console.log('  baies      :', strip($el('#bays').innerHTML), '| colonnes :', $el('#bays').style.gridTemplateColumns);
  console.log('  raid       :', strip($el('#md').innerHTML));
  console.log('  alerte     :', $el('#alarm').style.display, '|', $el('#alarmt').textContent);
  const bad = /degraded/.test(f);
  check('2 baies affichées', ($el('#bays').innerHTML.match(/class="bay"/g) || []).length === 2);
  check('modèle Duo', /ReadyNAS Duo/.test($el('#sub').textContent));
  check('mémoire utilisée jamais négative', /^\d+ (ko|Mo) \/ 221 Mo$/.test($el('#memt').textContent));
  check('écran masqué', $el('body').classList.set.has('nolcd'));
  check('X-RAID affiché', /X-RAID · Système/.test($el('#md').innerHTML) && /X-RAID · Données/.test($el('#md').innerHTML));
  check(bad ? 'alerte RAID dégradé visible' : 'pas d’alerte', bad ? ($el('#alarm').style.display === 'flex' && /RAID dégradé/.test($el('#alarmt').textContent)) : $el('#alarm').style.display === 'none');
  check(bad ? 'disque hde signalé en panne' : 'disques sains', bad ? /led bad/.test($el('#bays').innerHTML) && /failed/.test($el('#bays').innerHTML) : !/led bad/.test($el('#bays').innerHTML));
  if (bad) check('avancement de synchronisation', /Synchronisation : 25\.0 %/.test($el('#md').innerHTML));
  check(bad ? 'problème SMART signalé (baie et bandeau)' : 'SMART OK affiché avec les heures de marche',
        bad ? /12 secteurs réalloués/.test($el('#bays').innerHTML) && /Disque à surveiller : baie 2/.test($el('#alarmt').textContent)
            : /SMART OK · \d+ h de marche/.test($el('#bays').innerHTML));
}
// Masquer l'avertissement SMART : il disparaît, revient si son texte change, et ne cache jamais une alerte grave
{
  const store = {}; global.localStorage = { getItem: k => store[k] ?? null, setItem: (k, v) => { store[k] = v; } };
  const ok = JSON.parse(fs.readFileSync(process.argv[3], 'utf8')), bad = JSON.parse(fs.readFileSync(process.argv[4], 'utf8'));
  const warn = JSON.parse(JSON.stringify(ok)); warn.disks[0].smart.pending = 2;
  console.log('--- masquer l’avertissement');
  render(warn);
  check('avertissement SMART affiché avec le bouton', $el('#alarm').style.display === 'flex' && /baie 1 \(2 secteurs en attente\)/.test($el('#alarmt').textContent) && $el('#alarmx').style.display === '');
  hideWarning();
  check('masqué après le clic', $el('#alarm').style.display === 'none');
  render(warn);
  check('reste masqué aux rafraîchissements suivants', $el('#alarm').style.display === 'none');
  check('la baie reste signalée en rouge', /2 secteurs en attente/.test($el('#bays').innerHTML));
  warn.disks[0].smart.pending = 5; render(warn);
  check('revient si le nombre de secteurs change', $el('#alarm').style.display === 'flex' && /5 secteurs en attente/.test($el('#alarmt').textContent));
  render(bad); hideWarning();
  check('une alerte RAID ne peut pas être masquée', $el('#alarm').style.display === 'flex' && /RAID dégradé/.test($el('#alarmt').textContent) && !/Disque à surveiller/.test($el('#alarmt').textContent) && $el('#alarmx').style.display === 'none');
  delete global.localStorage;
}
// Langue : détection, traductions allemande et anglaise, dictionnaire complet
{
  console.log('--- langue');
  check('langue du navigateur (fr-FR) détectée', getLang() === 'fr');
  const ok = JSON.parse(fs.readFileSync(process.argv[3], 'utf8')), bad = JSON.parse(fs.readFileSync(process.argv[4], 'utf8'));
  setLang('de'); render(bad);
  check('allemand : baies, unités et alerte', /Schacht 1/.test($el('#bays').innerHTML) && /750 GB/.test($el('#bays').innerHTML) && /RAID beeinträchtigt/.test($el('#alarmt').textContent) && /Synchronisation: 25\.0 %/.test($el('#md').innerHTML));
  setLang('en'); render(ok);
  check('anglais : état et espace libre', /healthy/.test($el('#md').innerHTML) && /free of .* % used/.test($el('#cfreet').textContent) && /Bay 2/.test($el('#bays').innerHTML));
  check('séparateur décimal selon la langue', /^585\.5 GB$/.test($el('#cfree').textContent));
  setLang('de'); render(ok); check('virgule décimale en allemand', /^585,5 GB$/.test($el('#cfree').textContent));
  setLang('fr');
  // chaque texte traduisible a ses deux traductions, avec les mêmes {0} {1}
  const html = fs.readFileSync(process.env.DIET_HTML, 'utf8'), script = html.split('<script>')[1];
  const keys = new Set([...script.matchAll(/\bt\('((?:[^'\\]|\\.)*)'/g)].map(m => m[1].replace(/\\'/g, "'")));
  const body = html.split('<body>')[1].split('<script>')[0];
  for (const m of body.matchAll(/>([^<>]+)</g)) { const k = m[1].trim().replace(/\s+/g, ' '); if (/[a-zà-ÿ]{3}/i.test(k)) keys.add(k); }
  for (const m of body.matchAll(/(?:placeholder|title|data-q)="([^"]+)"/g)) keys.add(m[1]);
  const same = new Set(['NAS', 'CPU', 'Samba smbd', 'Samba nmbd', 'SMART OK', 'Français', 'Deutsch', 'English']);
  const missing = [...keys].filter(k => !same.has(k) && !I18N[k]);
  const bad2 = Object.entries(I18N).filter(([k, v]) => v.length !== 2 || v.some(x => !x) ||
    v.some(x => (x.match(/\{\d\}/g) || []).sort().join() !== (k.match(/\{\d\}/g) || []).sort().join()));
  if (missing.length) console.log('  sans traduction :', missing);
  if (bad2.length) console.log('  traductions incomplètes :', bad2.map(e => e[0]));
  check('tous les textes de la page ont une traduction (' + keys.size + ' textes)', !missing.length);
  check('traductions complètes et cohérentes (' + Object.keys(I18N).length + ' entrées)', !bad2.length);
}
// Historique : trois mesures dont une sans température (disques en veille)
global.fetch = async () => ({ ok: true, text: async () => '1000 38 1875 50\n1060 - 1870 50\n1120 40 1930 60\n' });
loadHist().then(() => {
  const h = $el('#hist').innerHTML;
  console.log('--- historique\n  ', strip(h));
  check('deux courbes tracées', (h.match(/<svg/g) || []).length === 2);
  check('plages de valeurs', /38–40 °C/.test(h) && /1870–1930 tr\/min/.test(h));
  check('trou dans la courbe quand la température est inconnue', /M0\.00 [\d.]+M100\.00/.test(h));
  process.exit(fail ? 1 : 0);
});
