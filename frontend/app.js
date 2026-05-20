(function () {
  const AUTO_PLAY_MS = 600;

  let steps = [];
  let config = {};
  let currentIdx = 0;
  let timer = null;
  let playing = false;

  /* ---- DOM refs ---- */
  const $ = (s) => document.querySelector(s);

  const dom = {
    algorithmBadge: $('#algorithmBadge'),
    progressFill: $('#progressFill'),
    progressText: $('#progressText'),
    instructionNo: $('#instructionNo'),
    pageNo: $('#pageNo'),
    offset: $('#offset'),
    physicalAddress: $('#physicalAddress'),
    resultCard: $('#resultCard'),
    resultIcon: $('#resultIcon'),
    resultText: $('#resultText'),
    loadedPage: $('#loadedPage'),
    victimPage: $('#victimPage'),
    memoryBlocks: $('#memoryBlocks'),
    pageFaultCount: $('#pageFaultCount'),
    pageFaultRate: $('#pageFaultRate'),
    btnReset: $('#btnReset'),
    btnPrev: $('#btnPrev'),
    btnPlay: $('#btnPlay'),
    btnPause: $('#btnPause'),
    btnNext: $('#btnNext'),
  };

  /* ---- helpers ---- */
  function pageLabel(p) {
    if (p === -1 || p === null || p === undefined) return '无';
    return String(p);
  }

  /* ---- render ---- */
  function render() {
    if (steps.length === 0) return;

    const s = steps[currentIdx];
    const total = steps.length;
    const pct = ((currentIdx + 1) / total * 100).toFixed(1);

    dom.progressFill.style.width = pct + '%';
    dom.progressText.textContent = (currentIdx + 1) + ' / ' + total;

    dom.instructionNo.textContent = s.instructionNo;
    dom.pageNo.textContent = s.pageNo;
    dom.offset.textContent = s.offset;
    dom.physicalAddress.textContent = s.physicalAddress;

    /* hit or fault */
    if (s.pageFault) {
      dom.resultCard.className = 'card result-card fault';
      dom.resultIcon.textContent = '✘';
      dom.resultText.textContent = '缺页';
    } else {
      dom.resultCard.className = 'card result-card hit';
      dom.resultIcon.textContent = '✔';
      dom.resultText.textContent = '命中';
    }

    dom.loadedPage.textContent = pageLabel(s.loadedPage);
    dom.victimPage.textContent = pageLabel(s.victimPage);

    /* memory blocks */
    const blocks = dom.memoryBlocks.children;
    for (let i = 0; i < blocks.length; i++) {
      const page = s.memoryState[i];
      blocks[i].className = 'memory-block';
      if (page === -1) {
        blocks[i].textContent = '空闲';
        blocks[i].classList.add('free');
      } else {
        blocks[i].textContent = '页 ' + page;
        blocks[i].classList.add('occupied');
      }
      if (i === s.blockNo) {
        blocks[i].classList.add('active');
      }
    }

    dom.pageFaultCount.textContent = s.pageFaultCount;
    dom.pageFaultRate.textContent = (s.pageFaultRate * 100).toFixed(1) + '%';

    /* button states */
    dom.btnPrev.disabled = (currentIdx === 0);
    dom.btnNext.disabled = (currentIdx === total - 1);
  }

  /* ---- navigation ---- */
  function goTo(idx) {
    if (idx < 0 || idx >= steps.length) return;
    currentIdx = idx;
    render();
  }

  function stepPrev() {
    if (playing) return;
    goTo(currentIdx - 1);
  }

  function stepNext() {
    if (playing) return;
    if (currentIdx >= steps.length - 1) {
      pause();
      return;
    }
    goTo(currentIdx + 1);
  }

  function reset() {
    pause();
    goTo(0);
  }

  function play() {
    if (steps.length === 0) return;
    if (currentIdx >= steps.length - 1) {
      currentIdx = 0;
    }
    playing = true;
    dom.btnPlay.style.display = 'none';
    dom.btnPause.style.display = '';
    dom.btnPrev.disabled = true;
    dom.btnNext.disabled = true;
    timer = setInterval(() => {
      if (currentIdx >= steps.length - 1) {
        pause();
        return;
      }
      goTo(currentIdx + 1);
    }, AUTO_PLAY_MS);
  }

  function pause() {
    playing = false;
    clearInterval(timer);
    timer = null;
    dom.btnPlay.style.display = '';
    dom.btnPause.style.display = 'none';
    dom.btnPrev.disabled = (currentIdx === 0);
    dom.btnNext.disabled = (currentIdx === steps.length - 1);
  }

  /* ---- keyboard ---- */
  function onKey(e) {
    if (e.key === 'ArrowLeft')  stepPrev();
    if (e.key === 'ArrowRight') stepNext();
    if (e.key === ' ')          { e.preventDefault(); playing ? pause() : play(); }
    if (e.key === 'r' || e.key === 'R') reset();
  }

  /* ---- load ---- */
  function loadData(data) {
    steps = data.steps || [];
    config = data;
    dom.algorithmBadge.textContent = config.algorithm || '-';
    reset();
  }

  function load() {
    if (window.SIMULATION_DATA) {
      loadData(window.SIMULATION_DATA);
      return;
    }

    fetch('../output/simulation_result.json')
      .then((r) => {
        if (!r.ok) throw new Error('HTTP ' + r.status);
        return r.json();
      })
      .then(loadData)
      .catch(() => {
        dom.resultText.textContent =
          '数据加载失败。请先运行 simulator 生成 output/simulation_data.js，' +
          '或使用 python3 -m http.server 8000 启动本地服务器。';
      });
  }

  /* ---- bind ---- */
  dom.btnPrev.addEventListener('click', stepPrev);
  dom.btnNext.addEventListener('click', stepNext);
  dom.btnReset.addEventListener('click', reset);
  dom.btnPlay.addEventListener('click', play);
  dom.btnPause.addEventListener('click', pause);
  document.addEventListener('keydown', onKey);

  load();
})();
